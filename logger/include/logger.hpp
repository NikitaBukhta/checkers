#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <fstream>
#include <memory>
#include <sstream>

class Logger{
public:
    enum class Level{
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

private:
    static std::mutex m_console_output_mutex;
    static std::mutex m_file_output_mutex;

    static std::string m_file_name;

    static std::fstream m_log_file;

    static bool m_output_logs_to_console;
    static bool m_logging_on;

    static Level m_min_lvl;
    static Level m_max_lvl;

public:

    static void do_log(const std::string &msg, Level log_lvl = Level::TRACE);

    static void set_file_name(const std::string &file_name);

    static std::string ptr_to_string(const void *const ptr);

    static void turn_output_logs_to_console(bool turn) noexcept;

    static void turn_logging(bool turn) noexcept;

    static void set_min_lvl(Level min_lvl) noexcept;

    static void set_max_lvl(Level max_lvl) noexcept;

private:
    Logger(void) = delete;

    static std::string log_to_string(Level log_lvl);

    static void output_log_to_console(const std::string &log_msg);

    static void output_log_to_file(const std::string &log_msg);
};

#endif // !LOGGER_HPP