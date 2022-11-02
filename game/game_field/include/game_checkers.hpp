#ifndef GAME_CHECKERS_HPP
#define GAME_CHECKERS_HPP

#include <memory>
#include <iostream>

#include "igame.hpp"
#include "checker.hpp"
#include "game_field.hpp"
#include "player.hpp"

namespace game{
    class GameCheckers : public IGame{
    private:
        static constexpr short m_START_ROWS_COUNT {3};      // Count of checkers' rows for one
        static constexpr short m_START_CHECKERS_IN_ROW {4}; // Count of checkers in row at start;
        GameField m_game_filed;

    public:
        int start(void) override;
        
        /* Descriptions:
         *  Return count of checkers in row at the start spawn;
         */
        static short get_start_checkers_in_row(void) noexcept;

        /* Descriptions:
         *  Return count of rows with checkers at the start spawn;
         */
        static short get_start_rows_count(void) noexcept;
    };
}

#endif // !GAME_CHECKERS_HPP