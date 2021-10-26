#pragma once
#include <memory>
#include <spdlog/spdlog.h>

namespace Wheel {

    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define WHEEL_CORE_TRACE(...) ::Wheel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WHEEL_CORE_INFO(...) ::Wheel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WHEEL_CORE_WARN(...) ::Wheel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WHEEL_CORE_ERROR(...) ::Wheel::Log::GetCoreLogger()->error(__VA_ARGS__)

#define WHEEL_TRACE(...) ::Wheel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define WHEEL_INFO(...) ::Wheel::Log::GetClientLogger()->info(__VA_ARGS__)
#define WHEEL_WARN(...) ::Wheel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WHEEL_ERROR(...) ::Wheel::Log::GetClientLogger()->error(__VA_ARGS__)



