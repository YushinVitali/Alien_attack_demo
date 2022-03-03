/// @file logger.hpp
/// @brief Description of the logging class.
#pragma once

#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <string>
#include <system_error>


/// @brief The type of the logged message.
enum class LOG_TYPE : int8_t
{
	MIN			= 0,	// Don't use! To turn off logging.
	ERROR,
	WARNING,
	INFO,
	DEBUG,
	MAX					// Don't use! To turn on full logging.
};


/// @brief Data logging class.
class Logger
{
public:
	static Logger* Instance();

	void LoggerWrite(const std::string& message,
					LOG_TYPE type = LOG_TYPE::DEBUG) const;
	void LoggerWrite(const std::error_code& errorCode,
					 const std::string& message = "",
					 LOG_TYPE type = LOG_TYPE::ERROR) const;

	void SetLogfile(const std::string& logFileName);
	std::string GetLogfile() const noexcept;

	void SetMaxLogLevel(LOG_TYPE maxLogLevel);
	void SetMaxLogLevel(int8_t maxLogLevel);
	int8_t GetMaxLogLevel() const noexcept;

private:
	Logger() {}
	Logger(const Logger&);
	Logger& operator=(Logger&);

	~Logger() {}

	/// @brief Get the current date and time.
	///
	/// @details In DD:MM:YYYY HH:MM:SS format.
	///
	/// @return Current date and time.
	std::string GetTime() const;

	bool IsLimitedMaxLogLevel(LOG_TYPE type) const;
	bool IsValidMaxLogLevel(int8_t logLevel) const;

private:
	static Logger* m_instance;

	std::string m_logFileName;		///< Full path to the log file.

	int8_t m_maxLogLevel{ static_cast<int8_t>(LOG_TYPE::MAX) };
};


/// @brief Function for logging.
void lout(LOG_TYPE type, const std::string& msg);

/// @brief Function for logging error_code.
void lout(LOG_TYPE type, std::error_code errorCode);

/// @brief Function for logging message and error_code.
void lout(LOG_TYPE type, const std::string& msg, std::error_code errorCode);

/// @brief Function for logging messages with the Debug logging type.
void loutd(const std::string& msg);

/// @brief Function for logging errors, error_code.
void lerr(std::error_code errorCode);

/// @brief Function for logging errors, error message and error_code.
void lerr(const std::string& msg, std::error_code errorCode);

/// @brief Get a string representation of the logging type.
std::string ToString(LOG_TYPE type);

#endif	// !__LOGGER_HPP__
