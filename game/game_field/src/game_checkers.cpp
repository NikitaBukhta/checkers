#include "game_checkers.hpp"

namespace game{
    GameCheckers::GameCheckers(void){
        Logger::do_log("GameCheckers constructor called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);

        m_player_1.reset(new Player(Color::WHITE, L"Player_1"));
        m_player_2.reset(new Player(Color::BLACK, L"Player_2"));
    }

    int GameCheckers::start(void){
        Logger::do_log("Game started", Logger::Level::TRACE);

        std::deque<std::shared_ptr<Checker>> player_1_checkers;
        std::deque<std::shared_ptr<Checker>> player_2_checkers;

        m_player_1->get_checkers(player_1_checkers);
        m_player_2->get_checkers(player_2_checkers);

        m_game_filed.add_checkers(player_1_checkers);
        m_game_filed.add_checkers(player_2_checkers);

        m_game_filed.draw_game_field();

        return 0;
    }
    
    void GameCheckers::make_move_to(const Coord &old_coord, const Coord &new_coord){
        Player *current_player;

        switch (m_current_move){
            case CurrentMove::PLAYER_1:
                current_player = m_player_1.get();
                break;
            case CurrentMove::PLAYER_2:
                current_player = m_player_2.get();
                break;
        }
    }
}