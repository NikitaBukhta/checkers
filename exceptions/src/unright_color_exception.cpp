#include "unright_color_exception.hpp"

namespace game{
    const char* UnrightColorException::what(void) const noexcept{
        return m_error_message.c_str();
    }
}