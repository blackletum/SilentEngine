#pragma once

namespace Silent::Utils
{
    // @todo Export "AVI: Uncompressed RGB" using jPSXdec and run this command:
    // ffmpeg -i INPUT.avi -r 30 -c:v mpeg1video -q:v 1 -c:a mp2 -ar 44100 -ac 2 OUTPUT.mpg

    /** @brief MPEG1 video player. */
    class VideoPlayer
    {
    private:
        // =======
        // Fields
        // =======

        plm_t*             _plm         = nullptr;
        std::vector<byte>  _frameBuffer = {};
        std::vector<float> _audioBuffer = {};
        std::mutex         _audioMutex  = {};

        std::string           _activeVideoName = {};
        std::filesystem::path _videosPath      = {};

    public:
        // =============
        // Constructors
        // =============

        /** @brief Creates a default uninitialized instance. */
        VideoPlayer() = default;

        /** @brief Gracefully destroys the instance and frees resources. */
        ~VideoPlayer();

        // ========
        // Getters
        // ========

        /** @brief Gets the active video's resolution.
         *
         * @return Video pixel resolution.
         */
        Vector2i GetResolution() const;

        /** @brief Gets the name of the active video.
         *
         * @return Active video name.
         */
        const std::string& GetVideoName() const;

        /** @brief Gets the video frame image for the current time in the video.
         *
         * @return RGBA video frame image.
         */
        const std::vector<byte>& GetVideoFrame() const;

        /** @brief Gets the audio frame samples for the current time in the video.
         *
         * @return Audio frame samples.
         */
        std::vector<float> GetAudioFrame();

        // ==========
        // Inquirers
        // ==========

        /** @brief Checks if a video is playing and hasn't ended.
         *
         * @return `true` if a video is playing and hasn't ended, `false` otherwise.
         */
        bool IsPlaying() const;

        // ==========
        // Utilities
        // ==========

        /** @brief Initializes the instance with a reference videos path
         *
         * @param videosPath Path containing videos.
         */
        void Initialize(const std::filesystem::path& videosPath);

        /** @brief Loads a new video to play.
         *
         * @param filename Video filename.
         * @return `true` if the video loaded successfully, `false` otherwise.
         */
        bool Load(const std::string& filename);

        /** @brief Progresses the video stream.
         *
         * @param deltaTime Progression time in seconds.
         */
        void Update(float deltaTime);

        /** @brief Closes the active video and  frees resources. */
        void Close();

        /** @brief Appends interleaved audio samples to the internal playback buffer.
         *
         * @param samples Array of float samples (L/R interleaved).
         * @param count Number of individual float values to append (`frames * channels`).
         */
        void AppendAudio(const float* samples, int count);
    };
}
