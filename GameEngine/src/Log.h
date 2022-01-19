#pragma once
#include "spdlog/spdlog.h"
#include <map>
#include <iostream>

class Log
{

private:

	static std::shared_ptr<spdlog::logger> logApp;
	static std::shared_ptr<spdlog::logger> logAuxiliar;
	static std::shared_ptr<spdlog::logger> logInputSystem;
	static std::shared_ptr<spdlog::logger> lastLogger;

public:

	static void Init();
	
	static std::shared_ptr<spdlog::logger>& getLogApp() { return logApp; };
	static std::shared_ptr<spdlog::logger>& getLogAuxiliar() { return logAuxiliar; };
	static std::shared_ptr<spdlog::logger>& getLogInputSystem() { return logInputSystem; };
	static void debug(std::shared_ptr<spdlog::logger> log,std::string mssg, spdlog::level::level_enum mode);

};

