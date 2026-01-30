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
    
    void FilesystemManager::Initialize()
    {
        // Set workspace path.
        _workDir = SDL_GetPrefPath(APP_NAME, APP_NAME);

        // Set app path.
        _appDir = std::filesystem::current_path();

        // Set screenshots path.
        if (PLATFORM_TYPE == PlatformType::Unknown)
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
        _assetsDir   = _appDir  / ".." / ASSETS_DIR_NAME;
        _savegameDir = _workDir / SAVEGAME_DIR_NAME;

        // Check for assets directory.
        if (!std::filesystem::exists(_assetsDir))
        {
            throw std::runtime_error(Fmt("`{}` folder not found in application directory.", ASSETS_DIR_NAME));
        }

        // Create workspace directories.
        std::filesystem::create_directories(_workDir);
        std::filesystem::create_directories(_savegameDir);
    }
}
