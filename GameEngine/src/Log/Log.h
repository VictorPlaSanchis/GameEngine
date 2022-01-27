#pragma once
#include "spdlog/spdlog.h"

namespace vge {

	class Log
	{

	private:

		std::shared_ptr<spdlog::logger> logApp;
		std::shared_ptr<spdlog::logger> logAuxiliar;
		std::shared_ptr<spdlog::logger> logInputSystem;
		std::shared_ptr<spdlog::logger> logGraphicEngine;
		std::shared_ptr<spdlog::logger> lastLogger;

	public:

		void Init();

		static Log* get();

		std::shared_ptr<spdlog::logger>& getLogApp() { return logApp; };
		std::shared_ptr<spdlog::logger>& getLogAuxiliar() { return logAuxiliar; };
		std::shared_ptr<spdlog::logger>& getLogInputSystem() { return logInputSystem; };
		std::shared_ptr<spdlog::logger>& getLogGraphicEngine() { return logGraphicEngine; }

		void debug(std::shared_ptr<spdlog::logger> log, std::string mssg, spdlog::level::level_enum mode);

	};

	// DEBUG MACROS

#define _DEBUG_ true
#define _DEBUG_FILTER_INFO_ true
#define _DEBUG_FILTER_WARNING_ true
#define _DEBUG_FILTER_ERROR_ true

#if _DEBUG_
#if _DEBUG_FILTER_INFO_
#define DEBUG_APP_INFO(x) Log::get()->debug(Log::get()->getLogApp(),x,spdlog::level::info)
#define DEBUG_AUX_INFO(x) Log::get()->debug(Log::get()->getLogAuxiliar(),x,spdlog::level::info)
#define DEBUG_ISL_INFO(x) Log::get()->debug(Log::get()->getLogInputSystem(),x,spdlog::level::info)
#define DEBUG_GEL_INFO(x) Log::get()->debug(Log::get()->getLogGraphicEngine(),x,spdlog::level::info)
#else
#define DEBUG_APP_INFO(x)
#define DEBUG_AUX_INFO(x)
#define DEBUG_ISL_INFO(x)
#endif

#if _DEBUG_FILTER_WARNING_
#define DEBUG_APP_WARNING(x) Log::get()->debug(Log::get()->getLogApp(),x,spdlog::level::warn)
#define DEBUG_AUX_WARNING(x) Log::get()->debug(Log::get()->getLogAuxiliar(),x,spdlog::level::warn)
#define DEBUG_ISL_WARNING(x) Log::get()->debug(Log::get()->getLogInputSystem(),x,spdlog::level::warn)
#define DEBUG_GEL_WARNING(x) Log::get()->debug(Log::get()->getLogGraphicEngine(),x,spdlog::level::warn)
#else
#define DEBUG_APP_INFO(x)
#define DEBUG_AUX_INFO(x)
#define DEBUG_ISL_INFO(x)
#endif

#if _DEBUG_FILTER_ERROR_
#define DEBUG_APP_ERROR(x) Log::get()->debug(Log::get()->getLogApp(),x,spdlog::level::err)
#define DEBUG_AUX_ERROR(x) Log::get()->debug(Log::get()->getLogAuxiliar,x,spdlog::level::err)
#define DEBUG_ISL_ERROR(x) Log::get()->debug(Log::get()->getLogInputSystem(),x,spdlog::level::err)
#define DEBUG_GEL_ERROR(x) Log::get()->debug(Log::get()->getLogGraphicEngine(),x,spdlog::level::err)
#else
#define DEBUG_APP_ERROR(x)
#define DEBUG_AUX_ERROR(x)
#define DEBUG_ISL_ERROR(x)
#endif
#else
#define DEBUG_APP_INFO(x)
#define DEBUG_AUX_INFO(x)
#define DEBUG_ISL_INFO(x)
#define DEBUG_APP_WARNING(x)
#define DEBUG_AUX_WARNING(x)
#define DEBUG_ISL_WARNING(x)
#define DEBUG_APP_ERROR(x)
#define DEBUG_AUX_ERROR(x)
#define DEBUG_ISL_ERROR(x)
#endif



}