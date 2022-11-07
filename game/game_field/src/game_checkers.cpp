#include "game_checkers.hpp"

namespace game{
    GameCheckers::GameCheckers(void){
        player_1.reset(new Player(Color::WHITE, L"Player_1"));
        player_2.reset(new Player(Color::BLACK, L"Player_2"));
    }

    int GameCheckers::start(void){
        m_game_filed.add_checkers(player_1->get_checkers());
        m_game_filed.add_checkers(player_2->get_checkers());

        m_game_filed.draw_game_field();

        return 0;
    }
}