#include "Framework.h"
#include "Utils/Video.h"

#include "Application.h"
#include "Renderer/Common/Constants.h"

using namespace Silent::Renderer;

namespace Silent::Utils
{
    /** @brief Callback to convert an MPEG1 YCrCb frame to RGBA.
     *
     * @param plm PLM context.
     * @param samples Interleaved samples.
     * @param user User data for the RGBA video frame buffer.
     */
    static void OnVideoFrame(plm_t* plm, plm_frame_t* frame, void* user)
    {
        uint8* frameBuffer = (uint8*)user;
        plm_frame_to_rgba(frame, frameBuffer, frame->width * RGBA_COMP_COUNT);
    }

    /** @brief Callback to decode audio samples from an MPEG1 stream.
     *
     * @param plm PLM context.
     * @param samples Interleaved samples.
     * @param user User data for the video player.
     */
    static void OnAudioFrame(plm_t* plm, plm_samples_t* samples, void* user)
    {
        auto* player = (VideoPlayer*)user;
        player->AppendAudio(samples->interleaved, samples->count * 2);
    }

    VideoPlayer::~VideoPlayer()
    {
        Close();
    }

    Vector2i VideoPlayer::GetResolution() const
    {
        if (_plm == nullptr)
        {
            Debug::Log("Attempted to get video resolution with no video playing.", Debug::LogLevel::Warning);
            return Vector2i::Zero;
        }

        return Vector2i(plm_get_width(_plm), plm_get_height(_plm));
    }

    const std::string& VideoPlayer::GetVideoName() const
    {
        return _activeVideoName;
    }

    const std::vector<byte>& VideoPlayer::GetVideoFrame() const
    {
        if (_plm == nullptr)
        {
            Debug::Log("Attempted to get video frame with no video playing.", Debug::LogLevel::Warning);
        }

        return _frameBuffer;
    }

    std::vector<float> VideoPlayer::GetAudioFrame()
    {
        if (_plm == nullptr)
        {
            Debug::Log("Attempted to get audio frame with no video playing.", Debug::LogLevel::Warning);
            return {};
        }

        // @lock Restrict audio buffer access.
        {
            auto lock = std::lock_guard(_audioMutex);

            auto data = _audioBuffer;
            _audioBuffer.clear();
            return data;
        }
    }

    bool VideoPlayer::IsPlaying() const
    {
        if (_plm == nullptr)
        {
            return false;
        }

        return plm_has_ended(_plm) == 0;
    }

    void VideoPlayer::Initialize(const std::filesystem::path& videosPath)
    {
        _videosPath = videosPath;
    }

    bool VideoPlayer::Load(const std::string& filename)
    {
        const auto& fs = g_App.GetFilesystem();

        // Check if video player is initialized.
        if (_videosPath.empty())
        {
            Debug::Log(Fmt("Attempted to load video `{}` in uninitialized video player.", filename),
                       Debug::LogLevel::Warning);
            return false;
        }

        Close();

        _activeVideoName = filename;

        // Open video file.
        auto videoPath = fs.GetAssetsDirectory() / ASSETS_VIDEO_DIR_NAME / filename;
        _plm           = plm_create_with_filename(videoPath.string().c_str());
        if (_plm == nullptr)
        {
            Debug::Log(Fmt("Failed to load video `{}`.", filename), Debug::LogLevel::Warning);
            return false;
        }

        // Allocate frame buffer.
        auto res     = GetResolution();
        _frameBuffer = std::vector<byte>((res.x * res.y) * RGBA_COMP_COUNT);

        // Register callbacks.
        plm_set_audio_enabled(_plm, true);
        plm_set_video_decode_callback(_plm, OnVideoFrame, _frameBuffer.data());
        plm_set_audio_decode_callback(_plm, OnAudioFrame, this);

        Debug::Log(Fmt("Loaded video `{}`.", filename));
        return true;
    }

    void VideoPlayer::Update(float deltaTime)
    {
        if (_plm == nullptr)
        {
            Debug::Log("Attempted to update video with no video playing.", Debug::LogLevel::Warning);
            return;
        }

        plm_decode(_plm, deltaTime);
    }

    void VideoPlayer::Close()
    {
        if (_plm != nullptr)
        {
            plm_destroy(_plm);
            _plm = nullptr;
        }

        _frameBuffer = {};
        _audioBuffer = {};
        _activeVideoName   = {};
    }

    void VideoPlayer::AppendAudio(const float* samples, int count)
    {
        // @lock Restrict audio buffer access.
        {
            auto lock = std::lock_guard(_audioMutex);

            _audioBuffer.insert(_audioBuffer.end(), samples, samples + count);
        }
    }
}
