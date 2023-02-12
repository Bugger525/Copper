#pragma once

#include <string>
#include <format>
#include <source_location>

#define CU_DBG_CRITICAL(fmt, ...) cu::Debug::Critical(std::format(fmt, ##__VA_ARGS__));
#define CU_DBG_ERROR(fmt, ...) cu::Debug::Error(std::format(fmt, ##__VA_ARGS__));
#define CU_DBG_WARN(fmt, ...) cu::Debug::Warn(std::format(fmt, ##__VA_ARGS__));
#define CU_DBG_INFO(fmt, ...) cu::Debug::Info(std::format(fmt, ##__VA_ARGS__));

namespace cu
{
	class Debug
	{
	public:
		Debug() = delete;

		static void Critical(std::string_view str, const std::source_location& location = std::source_location::current());
		static void Error(std::string_view str, const std::source_location& location = std::source_location::current());
		static void Warn(std::string_view str, const std::source_location& location = std::source_location::current());
		static void Info(std::string_view str, const std::source_location& location = std::source_location::current());
	};
}