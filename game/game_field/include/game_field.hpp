#ifndef GAME_FIELD_HPP
#define GAME_FIELD_HPP

#include "checker.hpp"
#include "unright_color_exception.hpp"

#include <array>
#include <thread>
#include <iostream>
#include <deque>
#include <memory>

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

        /* Descriptions:
         *  Return game field size;
         */
        static Size get_game_field_size(void) noexcept;

        /* Descriptions:
         *  Draw game field in console;
         */
        void draw_game_field(void) const noexcept;

        /* Descriptions:
         *  Added new checkers to game field;
         * 
         * Args:
         *  checkers - list of checkers we need to add to game field;
         */
        void add_checkers(const std::deque<std::shared_ptr<Checker>> &checkers);

        /* Description:
         *  Clear game field from all elements;
         */
        void reset(void);

        /* Description:
         *  check if coord inside game field;
         *
         * Args:
         *  coord - coord we check;
         * 
         * Return values;
         *  true - if coord inside game field;
         *  false - in other case;
         */
        bool coord_in_game_field(const Coord &coord) const noexcept;
    };
}

#endif // !GAME_FIELD_HPP