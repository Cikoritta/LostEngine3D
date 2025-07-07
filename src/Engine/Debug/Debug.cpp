#include "Debug.hpp"

#include <fstream>
#include <chrono>
#include <filesystem>
#include <mutex>
#include <string>
#include <iostream>

#ifdef _WIN32
    #include <Windows.h>
#endif


std::mutex  le::Debug::m_mutex;

std::string le::Debug::m_logDirectory = "log";

le::Debug::LogMode le::Debug::m_logMode = le::Debug::LogMode::Disabled;

std::unordered_map<le::Debug::LogLevel, std::string> le::Debug::m_logColors =
{
    { LogLevel::Debug,   "\033[38;5;240m"}, 
	{ LogLevel::Info,    "\033[32m" },
	{ LogLevel::Warning, "\033[33m" },
	{ LogLevel::Error,   "\033[31m" }
};

std::unordered_map<le::Debug::LogLevel, std::string> le::Debug::m_loglevels =
{
    { LogLevel::Debug,   "[DEBUG]"   },
    { LogLevel::Info,    "[INFO]"    },
    { LogLevel::Warning, "[WARNING]" },
    { LogLevel::Error,   "[ERROR]"   }
};


void le::Debug::log(const std::string& message, const le::Debug::LogLevel level)
{
    if ((m_logMode == LogMode::Disabled) || message.empty())
		return;

    switch (m_logMode)
    {
    case LogMode::Console:

        writeLogConsole(message, level);

        break;

    case LogMode::File:

        writeLogFile(message, level);

        break;

    case LogMode::All:

        writeLogConsole(message, level);

        writeLogFile(message, level);

        break;
    }

    if (level == LogLevel::Error)
    {
        error(message);
    }
}

void le::Debug::error(const std::string& message)
{
    #ifdef _WIN32
        MessageBoxA(nullptr, message.c_str(), "Runtime error", MB_OK | MB_ICONERROR);
    #else
        std::fprintf(stderr, "Runtime error: %s\n", message.c_str());
    #endif

    std::exit(EXIT_FAILURE);
}


void le::Debug::writeLogFile(const std::string& message, const le::Debug::LogLevel level)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    try
    {
        if (message.empty())
            return;


        const auto now = std::chrono::system_clock::now();

        const auto floored = std::chrono::floor<std::chrono::seconds>(now);

        const auto local_time = std::chrono::zoned_time{ std::chrono::current_zone(), floored };


        const std::string time_str = std::format("{:%H:%M:%S}", local_time);

        const std::string date_str = std::format("{:%Y_%m_%d}", local_time);


        std::filesystem::create_directories(m_logDirectory);

        const std::filesystem::path filePath = std::filesystem::path(m_logDirectory) / std::format("log_{}.txt", date_str);


        std::ofstream logFile(filePath, std::ios_base::app);

        if (!logFile)
			return writeLogConsole("Failed to open log file: " + filePath.string(), level);


        logFile << m_loglevels[level] << std::format("[{}] {}\n", time_str, message);


        if (!logFile.good())
			return writeLogConsole("Failed to write to log file: " + filePath.string(), level);
    }
    catch (const std::exception& e)
    {
		return writeLogConsole("Exception while writing to log file: " + std::string(e.what()), level);
    }
}

void le::Debug::writeLogConsole(const std::string& message, const LogLevel level)
{
    std::cerr << m_logColors[level] << m_loglevels[level] << message << m_logColors[le::Debug::LogLevel::Debug] << std::endl;
}


void le::Debug::setLogDirectory(const std::string& directory)
{
    m_logDirectory = directory;
}


void le::Debug::setDebugMode(const le::Debug::LogMode mode)
{
    m_logMode = mode;
}
