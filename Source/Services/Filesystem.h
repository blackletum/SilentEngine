#pragma once

namespace Silent::Services
{
    constexpr char ASSETS_DIR_NAME[]             = "Assets";
    constexpr char SAVEGAME_DIR_NAME[]           = "Savegame";
    constexpr char SAVEGAME_FILE_DIR_NAME_BASE[] = "File ";
    constexpr char SCREENSHOTS_DIR_NAME[]        = "Screenshots";
    constexpr char SHADERS_DIR_NAME[]            = "Shaders";

    constexpr char OPTIONS_FILENAME[] = "Options";

    constexpr char JSON_FILE_EXT[]     = ".json";
    constexpr char PNG_FILE_EXT[]      = ".png";
    constexpr char SAVEGAME_FILE_EXT[] = ".save";
    
    constexpr int JSON_INDENT_SIZE = 4;

    /** @brief Filesystem manager. */
    class FilesystemManager
    {
    private:
        // =======
        // Fields
        // =======

        std::filesystem::path _appDir         = {}; /** Application folder. */
        std::filesystem::path _assetsDir      = {}; /** Game assets folder. */
        std::filesystem::path _workDir        = {}; /** Workspace folder. */
        std::filesystem::path _savegameDir    = {}; /** Savegame folder. */
        std::filesystem::path _screenshotsDir = {}; /** Screenshots folder. */
        std::filesystem::path _shadersDir     = {}; /** Shaders folder. */

    public:
        // =============
        // Constructors
        // =============

        FilesystemManager() = default;

        // ========
        // Getters
        // ========

        const std::filesystem::path& GetAppDirectory() const;
        const std::filesystem::path& GetAssetsDirectory() const;
        const std::filesystem::path& GetWorkDirectory() const;
        const std::filesystem::path& GetSavegameDirectory() const;
        const std::filesystem::path& GetScreenshotsDirectory() const;
        const std::filesystem::path& GetShadersDirectory() const;

        // ==========
        // Utilities
        // ==========

        /** @brief Initializes the filesystem. */
        void Initialize();
    };
}
