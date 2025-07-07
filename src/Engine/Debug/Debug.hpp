#pragma once
#include <mutex>
#include <unordered_map>
#include <format>

#include "../Common.hpp"


namespace le
{
	#define LOG_DEBUG(msg) \
    do { if constexpr (le::DEBUG_MODE) le::Debug::log((msg), le::Debug::LogLevel::Debug); } while (0)

	#define LOG_INFO(msg) \
    do { if constexpr (le::DEBUG_MODE) le::Debug::log((msg), le::Debug::LogLevel::Info); } while (0)

	#define LOG_WARN(msg) \
    do { if constexpr (le::DEBUG_MODE) le::Debug::log((msg), le::Debug::LogLevel::Warning); } while (0)

	#define LOG_ERROR(msg) \
    do { if constexpr (le::DEBUG_MODE) le::Debug::log((msg), le::Debug::LogLevel::Error); } while (0)

	class Debug
	{
	public:

		enum class LogLevel : std::uint8_t
		{
			Debug,
			Info,
			Warning,
			Error
		};

		enum class LogMode : std::uint8_t
		{
			Disabled,
			Console,
			File,
			All
		};

	private:

		static std::mutex m_mutex;

		static std::string m_logDirectory;


		static LogMode m_logMode;


		static void error(const std::string& message);


		static void writeLogFile(const std::string& message, const LogLevel level);

		static void writeLogConsole(const std::string& message, const LogLevel level);


		static std::unordered_map<LogLevel, std::string> m_logColors;

		static std::unordered_map<LogLevel, std::string> m_loglevels;

	public:

		static void log(const std::string& message, const LogLevel level);


		static void setLogDirectory(const std::string& directory);


		static void setDebugMode(const LogMode mode);
	};
}
