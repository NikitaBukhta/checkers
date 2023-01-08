#include "wrong_checker_move_exception.hpp"

namespace game{
    const char* WrongCheckerMoveException::what(void) const noexcept{
        return m_error_message.c_str();
    }
}