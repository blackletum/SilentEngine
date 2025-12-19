#include "Framework.h"
#include "Services/Platform.h"

namespace Silent::Services
{
    std::filesystem::path GetHomeDirectory()
    {
#if defined(_WIN32) || defined(_WIN64)
        char*  buffer = nullptr;
        size_t length = 0;

        if (_dupenv_s(&buffer, &length, "USERPROFILE") == 0 && buffer != nullptr)
        {
            auto home = std::string(buffer);
            free(buffer);
            return std::filesystem::path(home);
        }

        return {};
#else
        return std::filesystem::path(getenv("HOME"));
#endif
    }

    /** @brief Handles a termination exception. */
    static void TerminateHandler()
    {
        CriticalErrorHandler("Unhandled exception.");
    }

    /** @brief Handles a signal exception.
     *
     * @param signal Signal ID.
     */
    static void SignalHandler(int signal)
    {
        auto msg = std::string();
        switch (signal)
        {
            case SIGILL:
            {
                msg = "Illegal instruction (`SIGILL`).";
                break;
            }
            case SIGFPE:
            {
                msg = "Floating point exception (`SIGFPE`).";
                break;
            }
            case SIGSEGV:
            {
                msg = "Segment violation (`SIGSEGV`).";
                break;
            }
            case SIGABRT:
            {
                msg = "Abort (`SIGABRT`).";
                break;
            }
            case SIGTERM:
            {
                msg = "Graceful termination (`SIGTERM`).";
                break;
            }
            default:
            {
                msg = Fmt("Unhandled signal {} occurred.", signal);
                break;
            }
        }

        CriticalErrorHandler(msg);
    }

    void InitializeSignals()
    {
        std::set_terminate(TerminateHandler);
        std::signal(SIGILL,  SignalHandler);
        std::signal(SIGFPE,  SignalHandler);
        std::signal(SIGSEGV, SignalHandler);
        std::signal(SIGTERM, SignalHandler);
        std::signal(SIGABRT, SignalHandler);
    }

    void CriticalErrorHandler(const std::string& msg)
    {
        Debug::Log(msg, Debug::LogLevel::Critical);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Critical Error", msg.c_str(), nullptr);
    }
}
