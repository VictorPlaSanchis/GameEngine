#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::logApp;
std::shared_ptr<spdlog::logger> Log::logAuxiliar;
std::shared_ptr<spdlog::logger> Log::logInputSystem;
std::shared_ptr<spdlog::logger> Log::lastLogger;

void Log::Init()
{
    spdlog::set_pattern("%^[%T] %n:  %v%$");
    logApp = spdlog::stderr_color_mt("APP");
    logApp->set_level(spdlog::level::trace);
    logAuxiliar = spdlog::stderr_color_mt("AUX");
    logAuxiliar->set_level(spdlog::level::debug);
    logInputSystem = spdlog::stderr_color_mt("ISL");
    logInputSystem->set_level(spdlog::level::trace);
}

void Log::debug(std::shared_ptr<spdlog::logger> log, std::string mssg, spdlog::level::level_enum mode)
{
    if (log == Log::lastLogger) spdlog::set_pattern("\t\t %v%$");
    else spdlog::set_pattern("%^[%T] %n:  %v%$");
    
    switch (mode) {
        case spdlog::level::warn:
            log->warn(mssg);
            break;
        case spdlog::level::err:
            log->error(mssg);
            break;
        case spdlog::level::debug:
            log->debug(mssg);
            break;
        case spdlog::level::info:
            log->info(mssg);
            break;
        default:
            log->warn(mssg);
    }

    Log::lastLogger = log;

}
