#ifndef GAME_FIELD_HPP
#define GAME_FIELD_HPP

#include "checker.hpp"

#include <array>
#include <thread>
#include <iostream>

namespace game{
    struct Size{
        short width;
        short height;
    };

    class GameField{
    private:
        static constexpr short m_START_ROWS_COUNT {3};
        static constexpr short m_START_CHECKERS_IN_ROW {4};
        static constexpr Size m_GAME_FIELD_SIZE{8, 8};

        std::array<std::array<short, m_GAME_FIELD_SIZE.width>, m_GAME_FIELD_SIZE.height> m_field = {0};

    public:
        GameField(void);

        static Size get_game_field_size(void) noexcept;

        void draw_game_field(void) const noexcept;

    private:
        void fill_checkers_field_with(Color checker_color);
    };
}

#endif // !GAME_FIELD_HPP