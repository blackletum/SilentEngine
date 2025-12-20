#pragma once

namespace Silent::Services
{
    /** @brief Supported operating systems. */
    enum class OsType
    {
        Unknown,
        Windows,
        MacOs,
        Linux
    };

    constexpr auto OS_TYPE = 
#if defined(_WIN32) || defined(_WIN64)
    OsType::Windows;
#elif defined(__APPLE__)
    OsType::MacOs;
#elif defined(__linux__)
    OsType::Linux;
#else
    OsType::Unknown;
#endif

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
