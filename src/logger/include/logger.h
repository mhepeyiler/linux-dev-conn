#ifndef LINUX_DEV_CONN_SRC_LOGGER_LOGGER_H
#define LINUX_DEV_CONN_SRC_LOGGER_LOGGER_H

#if LOG

#include <cstdio>
#include <sstream>
#include <iomanip>
#include <atomic>
#include <cstring>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_TRACE(str, ...) Logger::log("TRACE", __FILENAME__, __func__, __LINE__, str, ##__VA_ARGS__)
#define LOG_DEBUG(str, ...) Logger::log("DEBUG", __FILENAME__, __func__, __LINE__, str, ##__VA_ARGS__)
#define LOG_INFO(str, ...) Logger::log("INFO", __FILENAME__, __func__, __LINE__, str, ##__VA_ARGS__)
#define LOG_WARN(str, ...) Logger::log("WARN", __FILENAME__, __func__, __LINE__, str, ##__VA_ARGS__)
#define LOG_ERROR(str, ...) Logger::log("ERROR", __FILENAME__, __func__, __LINE__, str, ##__VA_ARGS__)
#define LOG_FATAL(str, ...) Logger::log("FATAL", __FILENAME__, __func__, __LINE__, str, ##__VA_ARGS__)

struct Logger {
    inline static std::atomic<size_t> logCount{};

    static void log(std::string_view level, const char* file, const char* func, int line, const char* str) {
        logCount++;
        std::stringstream ss;
        ss << level << " #" << std::setfill('0') << std::setw(5) << logCount;
        ss << std::setfill(' ') << std::setw(2)  << '{' << file << ':' << func << ':' << line << '}';
        ss << " "  << str << '\n';
        printf(ss.str().c_str());
    }        

    template<typename ...Args>
    static void log(std::string_view level, const char* file, const char* func, int line, const char* str, Args ...arg) {
        logCount++;
        std::stringstream ss;
        ss << level << " #" << std::setfill('0') << std::setw(5) << logCount;
        ss << std::setfill(' ') << std::setw(2)  << '{' << file << ':' << func << ':' << line << '}';
        ss << " "  << str << '\n';
        printf(ss.str().c_str(), arg...);
    }
};

#else 

#define LOG_TRACE(str, ...)
#define LOG_DEBUG(str, ...)
#define LOG_INFO(str, ...)
#define LOG_WARN(str, ...)
#define LOG_ERROR(str, ...)
#define LOG_FATAl(str, ...)

#endif

#endif