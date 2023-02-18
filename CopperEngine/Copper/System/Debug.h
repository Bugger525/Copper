#pragma once

#include <string>
#include <format>
#include <source_location>

#define CU_DBG_CRITICAL(fmt, ...) cu::sys::Debug::Critical(std::format(fmt, ##__VA_ARGS__));
#define CU_DBG_ERROR(fmt, ...) cu::sys::Debug::Error(std::format(fmt, ##__VA_ARGS__));
#define CU_DBG_WARN(fmt, ...) cu::sys::Debug::Warn(std::format(fmt, ##__VA_ARGS__));
#define CU_DBG_INFO(fmt, ...) cu::sys::Debug::Info(std::format(fmt, ##__VA_ARGS__));

namespace cu::sys
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