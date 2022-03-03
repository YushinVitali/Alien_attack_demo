/// @file logger.cpp
/// @brief Implementation of methods of the logging class.

#include <logger.hpp>

#include <fstream>
#include <sstream>
#include <time.h>


Logger* Logger::m_instance = nullptr;


Logger* Logger::Instance() {
	if(!m_instance) {
		m_instance = new Logger();
	}
	return m_instance;
}


void Logger::LoggerWrite(const std::string& message,
						LOG_TYPE type /* = LOG_TYPE::DEBUG */) const {
	if(m_logFileName.empty() || message.empty() || IsLimitedMaxLogLevel(type)) {
		return;
	}

	std::ofstream logFile(m_logFileName, std::ios_base::app);
	if(!logFile) {
		// ERROR.
		return;
	}

	logFile << '[' << GetTime() << "] - ";
	logFile << ToString(type) << ": ";
	logFile << message << std::endl;

	logFile.close();
}


void Logger::LoggerWrite(const std::error_code& errorCode,
						 const std::string& message /* = "" */,
						 LOG_TYPE type /* = LOG_TYPE::ERR*/) const {
	if (m_logFileName.empty() || IsLimitedMaxLogLevel(type)) {
		return;
	}

	std::ofstream logFile(m_logFileName, std::ios_base::app);
	if (!logFile) {
		// ERROR.
		return;
	}

	logFile << '[' << GetTime() << "] - ";
	logFile << ToString(type) << ": ";
	logFile << message << ' ';
	logFile << errorCode.message() << " [" << errorCode << "]" << std::endl;

	logFile.close();
}


void Logger::SetLogfile(const std::string& logFileName) {
	if (logFileName.empty()) {
		return;
	}

	m_logFileName = logFileName;

	std::ofstream logFile(m_logFileName, std::ios_base::trunc);
	logFile.close();
}


std::string Logger::GetLogfile() const noexcept {
	return m_logFileName;
}


void Logger::SetMaxLogLevel(LOG_TYPE maxLogLevel) {
	SetMaxLogLevel(static_cast<int8_t>(maxLogLevel));
}


void Logger::SetMaxLogLevel(int8_t maxLogLevel) {
	if(IsValidMaxLogLevel(maxLogLevel)) {
		m_maxLogLevel = maxLogLevel;
	}
}


int8_t Logger::GetMaxLogLevel() const noexcept {
	return m_maxLogLevel;
}


std::string Logger::GetTime() const {
	const time_t t{ time(nullptr) };
	const struct tm* timeinfo{ localtime( &t ) };

	// The countdown has been going on since 1900.
	const int32_t year{ timeinfo->tm_year + 1900 };
	// Month starts from 0.
	const int32_t month{ timeinfo->tm_mon + 1 };

	std::ostringstream dateToString;

	if (timeinfo->tm_mday < 10) {
		dateToString << '0';
	}

	dateToString << timeinfo->tm_mday << '.';

	if (month < 10) {
		dateToString << '0';
	}

	dateToString << month << '.' << year << ' '
		<< timeinfo->tm_hour << ':' << timeinfo->tm_min << ':' << timeinfo->tm_sec;

	return dateToString.str();
}


bool Logger::IsLimitedMaxLogLevel(LOG_TYPE type) const{
	return static_cast<int8_t>(type) > m_maxLogLevel;
}


bool Logger::IsValidMaxLogLevel(int8_t logLevel) const {
	return logLevel >= static_cast<int8_t>(LOG_TYPE::MIN) &&
		   logLevel <= static_cast<int8_t>(LOG_TYPE::MAX);
}


void lout(LOG_TYPE type, const std::string& msg) {
	Logger::Instance()->LoggerWrite(msg, type);
}


void lout(LOG_TYPE type, std::error_code errorCode) {
	Logger::Instance()->LoggerWrite(errorCode, "", type);
}


void lout(LOG_TYPE type, const std::string& msg, std::error_code errorCode) {
	Logger::Instance()->LoggerWrite(errorCode, msg, type);
}


void loutd(const std::string& msg) {
	Logger::Instance()->LoggerWrite(msg);
}


void lerr(std::error_code errorCode) {
	Logger::Instance()->LoggerWrite(errorCode);
}


void lerr(const std::string& msg, std::error_code errorCode) {
	Logger::Instance()->LoggerWrite(errorCode, msg);
}


std::string ToString(LOG_TYPE type) {
	switch (type) {
		case LOG_TYPE::ERROR: {
			return "ERROR";
		}
		case LOG_TYPE::WARNING: {
			return "WARNING";
		}
		case LOG_TYPE::INFO: {
			return "INFO";
		}
		case LOG_TYPE::DEBUG: {
			return "DEBUG";
		}

		default: {
			return "";
		}
	}
}
