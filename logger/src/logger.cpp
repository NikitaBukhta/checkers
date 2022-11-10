#include  "logger.hpp"

std::mutex Logger::m_console_output_mutex;
std::mutex Logger::m_file_output_mutex;

std::string Logger::m_file_name = "logger.log";

std::fstream Logger::m_log_file;

void Logger::do_log(const std::string &msg, Level log_lvl){
    std::string string_date;
    {
        std::time_t current_date = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        string_date = std::string(std::ctime(&current_date));
        string_date.pop_back();
    }
    std::string log_msg = string_date + "\t[" + log_to_string(log_lvl)
        + "]: " + msg;

    std::thread console_output_thread(&output_log_to_console, std::ref(log_msg));
    std::thread file_output_thread(&output_log_to_file, std::ref(log_msg));

    console_output_thread.join();
    file_output_thread.join();
}

void Logger::set_file_name(const std::string &file_name){
    if (m_log_file.is_open()){
        m_log_file.close();
    }

    m_file_name = file_name + ".log";
    m_log_file.open(m_file_name, std::ios::out);
}

std::string Logger::ptr_to_string(const void *const ptr){
    std::stringstream ptr_in_string;
    ptr_in_string << ptr;
    
    return ptr_in_string.str();
}

std::string Logger::log_to_string(Level log_lvl){
    switch(log_lvl){
    case Level::FATAL:
        return "FATAL";

    case Level::ERROR:
        return "ERROR";

    case Level::WARN:
        return "WARN";

    case Level::INFO:
        return "INFO";

    case Level::DEBUG:
        return "DEBUG";

    case Level::TRACE:
        return "TRACE";

    default:
        return "UNKNOWN";
    }
}

void Logger::output_log_to_console(const std::string &log_msg){
    std::lock_guard guard(m_console_output_mutex);
    std::cout << log_msg << std::endl;
}

void Logger::output_log_to_file(const std::string &log_msg){
    std::lock_guard guard(m_file_output_mutex);
    if (!m_log_file.is_open()){
        m_log_file.open(m_file_name, std::ios::out);
    }

    m_log_file << log_msg << std::endl;
}