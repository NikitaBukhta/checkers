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

private:
    static std::mutex m_console_output_mutex;
    static std::mutex m_file_output_mutex;

    static std::string m_file_name;

    static std::fstream m_log_file;

public:
    enum class Level{
        FATAL,
        ERROR,
        WARN,
        INFO,
        DEBUG,
        TRACE
    };

    static void do_log(const std::string &msg, Level log_lvl = Level::TRACE);

    static void set_file_name(const std::string &file_name);

    static std::string ptr_to_string(const void *const ptr);

private:
    Logger(void) = delete;

    static std::string log_to_string(Level log_lvl);

    static void output_log_to_console(const std::string &log_msg);

    static void output_log_to_file(const std::string &log_msg);
};

#endif // !LOGGER_HPP