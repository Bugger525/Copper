#pragma once

#include <string>
#include <format>
#include <source_location>

#define CU_DBG_CRITICAL(fmt, ...) Copper::Debug::Critical(std::format(fmt, ##__VA_ARGS__));
#define CU_DBG_ERROR(fmt, ...) Copper::Debug::Error(std::format(fmt, ##__VA_ARGS__));
#define CU_DBG_WARN(fmt, ...) Copper::Debug::Warn(std::format(fmt, ##__VA_ARGS__));
#define CU_DBG_INFO(fmt, ...) Copper::Debug::Info(std::format(fmt, ##__VA_ARGS__));

namespace Copper
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