#ifndef GAME_FIELD_HPP
#define GAME_FIELD_HPP

#include "checker.hpp"

#include <array>
#include <thread>
#include <iostream>
#include <deque>

namespace game{
    struct Size{
        short width;
        short height;
    };

    class GameField{
    private:
        static constexpr Size m_GAME_FIELD_SIZE{8, 8};

        std::array<std::array<Color, m_GAME_FIELD_SIZE.width>, m_GAME_FIELD_SIZE.height> m_field = {Color::NO_COLOR};

    public:
        GameField(void) = default;

        static Size get_game_field_size(void) noexcept;

        void draw_game_field(void) const noexcept;

        void add_checkers(const std::deque<Checker> &checkers);
    };
}

#endif // !GAME_FIELD_HPP