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

#if defined(_WIN32) || defined(_WIN64)
    constexpr auto OS_TYPE = OsType::Windows;
#elif defined(__APPLE__)
    constexpr auto OS_TYPE = OsType::MacOs;
#elif defined(__linux__)
    constexpr auto OS_TYPE = OsType::Linux;
#else
    constexpr auto OS_TYPE = OsType::Unknown;
#endif

    /** @brief Gets the platform's home directory.
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
