#pragma once

namespace Silent::Services
{
    /** @brief Supported platform types. */
    enum class PlatformType
    {
        Unknown,
        Windows,
        MacOs,
        Linux
    };

    constexpr auto PLATFORM_TYPE = 
#if defined(_WIN32) || defined(_WIN64)
                                   PlatformType::Windows;
#elif defined(__APPLE__)
                                   PlatformType::MacOs;
#elif defined(__linux__)
                                   PlatformType::Linux;
#else
                                   PlatformType::Unknown;
#endif

    /** @brief Gets the name of the OS.
     *
     * @return OS name.
     */
    std::string GetPlatformName();

    /** @brief Gets the platform-specific home directory.
     *
     * @return Home directory.
     */
    std::filesystem::path GetHomeDirectory();

    /** @brief Initializes low-level termination and signal handling. */
    void InitializeSignals();

    /** @brief Handles a critical error.
     *
     * @param msg Error message.
     */
    void CriticalErrorHandler(const std::string& msg);
}
