#ifndef WRONG_CHECKER_MOVE_HPP
#define WRONG_CHECKER_MOVE_HPP

#include <exception>
#include <string>

namespace game{
    class WrongCheckerMoveException : public std::exception{
    private:
        std::string m_error_message;
    
    public:
        WrongCheckerMoveException(const std::string &msg = "") : m_error_message(msg) {};

        virtual const char *what(void) const noexcept override;
    };
}

#endif // !WRONG_CHECKER_MOVE_HPP