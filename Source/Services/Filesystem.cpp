#include "Framework.h"
#include "Services/Filesystem.h"

#include "Application.h"
#include "Services/Platform.h"

namespace Silent::Services
{
    const std::filesystem::path& FilesystemManager::GetAppDirectory() const
    {
        return _appDir;
    }

    const std::filesystem::path& FilesystemManager::GetAssetsDirectory() const
    {
        return _assetsDir;
    }

    const std::filesystem::path& FilesystemManager::GetWorkDirectory() const
    {
        return _workDir;
    }

    const std::filesystem::path& FilesystemManager::GetSavegameDirectory() const
    {
        return _savegameDir;
    }

    const std::filesystem::path& FilesystemManager::GetScreenshotsDirectory() const
    {
        return _screenshotsDir;
    }
    
    const std::filesystem::path& FilesystemManager::GetShadersDirectory() const
    {
        return _shadersDir;
    }

    void FilesystemManager::Initialize()
    {
        constexpr char ASSETS_DIR_NAME[]      = "Assets";
        constexpr char SAVEGAME_DIR_NAME[]    = "Savegame";
        constexpr char SCREENSHOTS_DIR_NAME[] = "Screenshots";
        constexpr char SHADERS_DIR_NAME[]     = "Shaders";

        // Set workspace path.
        _workDir = SDL_GetPrefPath(APP_NAME, APP_NAME);

        // Set app path.
        _appDir = std::filesystem::current_path();

        // Set screenshots path.
        if (OS_TYPE == OsType::Unknown)
        {
            _screenshotsDir = _workDir / SCREENSHOTS_DIR_NAME;
        }
        else
        {
            auto homeDir = GetHomeDirectory();
            if (!homeDir.empty())
            {
                _screenshotsDir = homeDir / "Pictures" / SCREENSHOTS_DIR_NAME;
            }
        }

        // Set workspace paths.
        _assetsDir   = _appDir  / ASSETS_DIR_NAME;
        _savegameDir = _workDir / SAVEGAME_DIR_NAME;
        _shadersDir  = _appDir  / SHADERS_DIR_NAME;

        // Check for assets directory.
        if (!std::filesystem::exists(_assetsDir))
        {
            throw std::runtime_error(Fmt("`{}` folder not found in application directory.", ASSETS_DIR_NAME));
        }

        // Check for shaders directory.
        if (!std::filesystem::exists(_shadersDir))
        {
            throw std::runtime_error(Fmt("`{}` folder not found in application directory.", SHADERS_DIR_NAME));
        }

        // Create workspace directories.
        std::filesystem::create_directories(_workDir);
        std::filesystem::create_directories(_savegameDir);
    }
}
