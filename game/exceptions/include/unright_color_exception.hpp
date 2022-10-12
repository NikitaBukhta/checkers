#ifndef UNRIGHT_COLOR_EXCEPTION_HPP
#define UNRIGHT_COLOR_EXCEPTION_HPP

#include <exception>
#include <string>

namespace game{
    class UnrightColorException : public std::exception{
    private:
        std::string m_error_message;
    
    public:
        UnrightColorException(const std::string &msg = "") : m_error_message(msg) {};

        virtual const char *what(void) const noexcept override;
    };
}

#endif // !UNRIGHT_COLOR_EXCEPTION_HPP