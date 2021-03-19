#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Future
{
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

// Core log macros
#define FT_CORE_TRACE(...)    Future::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FT_CORE_ERROR(...)    Future::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FT_CORE_WARN(...)     Future::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FT_CORE_INFO(...)     Future::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FT_CORE_CRITICAL(...) Future::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define FT_TRACE(...)    Future::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FT_ERROR(...)    Future::Log::GetClientLogger()->error(__VA_ARGS__)
#define FT_WARN(...)     Future::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FT_INFO(...)     Future::Log::GetClientLogger()->info(__VA_ARGS__)
#define FT_CRITICAL(...) Future::Log::GetClientLogger()->critical(__VA_ARGS__)