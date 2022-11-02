#include "game_checkers.hpp"

namespace game{
    int GameCheckers::start(void){
        Player player_1(Color::WHITE, L"Player 1");
        Player player_2(Color::BLACK);

        m_game_filed.add_checkers(player_1.get_checkers());
        m_game_filed.add_checkers(player_2.get_checkers());

        m_game_filed.draw_game_field();

        return 0;
    }

    short GameCheckers::get_start_checkers_in_row(void) noexcept{
        return m_START_CHECKERS_IN_ROW;
    }

    short GameCheckers::get_start_rows_count(void) noexcept{
        return m_START_ROWS_COUNT;
    }
}