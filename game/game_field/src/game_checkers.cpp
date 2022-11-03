#include "game_checkers.hpp"

namespace game{
    GameCheckers::GameCheckers(void){
    }

    int GameCheckers::start(void){
        m_game_filed.add_checkers(player_1.get_checkers());
        m_game_filed.add_checkers(player_2.get_checkers());

        m_game_filed.draw_game_field();

        return 0;
    }
}