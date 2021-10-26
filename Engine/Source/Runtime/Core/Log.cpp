#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Wheel {

    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("Wheel");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("Game");
        s_ClientLogger->set_level(spdlog::level::trace);

        s_CoreLogger->info("Core Logger Initialized");
        s_ClientLogger->info("Client Logger Initialized");
    }
}