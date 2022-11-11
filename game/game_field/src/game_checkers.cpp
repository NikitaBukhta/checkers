#include "game_checkers.hpp"

namespace game{
    GameCheckers::GameCheckers(void){
        Logger::do_log("GameCheckers constructor called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);

        m_player_1.reset(new Player(Color::WHITE, L"Player_1"));
        m_player_2.reset(new Player(Color::BLACK, L"Player_2"));

        m_current_move = CurrentMove::PLAYER_1;
    }

    int GameCheckers::start(void){
        Logger::do_log("GameCheckers::start called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);

        std::deque<std::shared_ptr<Checker>> player_1_checkers;
        std::deque<std::shared_ptr<Checker>> player_2_checkers;

        Coord old_coord;
        Coord new_coord;
        while (true){
            // Reset game field to update the screen;
            std::thread game_field_reset_th (&GameField::reset, &m_game_filed);

            // Write players' checkers to deques;
            {
                std::thread player_1_th(&Player::get_checkers, m_player_1.get(), std::ref(player_1_checkers));
                std::thread player_2_th(&Player::get_checkers, m_player_2.get(), std::ref(player_2_checkers));
                player_1_th.join();
                player_2_th.join();
            }

            game_field_reset_th.join();

            // Added checkers to game field;
            {
                std::thread player_1_th(&GameField::add_checkers, &m_game_filed, std::ref(player_1_checkers));
                std::thread player_2_th(&GameField::add_checkers, &m_game_filed, std::ref(player_2_checkers));
                player_1_th.join();
                player_2_th.join();
            }

            m_game_filed.draw_game_field();

            output_current_turn_msg();

            // while right move is not completed;
            while (true){
                try{
                    get_move_coord(old_coord, new_coord);
                    make_move_to(old_coord, new_coord);
                    break;
                }
                catch(const WrongCheckerMoveException &error){
                    std::cerr << error.what() << std::endl << "Please, try again!";
                }
            }

            change_turn();
        }


        return 0;
    }
    
    void GameCheckers::make_move_to(const Coord &old_coord, const Coord &new_coord){
        Logger::do_log("GameCheckers::make_move_to called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);

        if (!m_game_filed.coord_in_game_field(new_coord)){
            Logger::do_log("GameCheckers::make_move_to (" + Logger::ptr_to_string(this) + ") throw WrongCheckerMoveException" +
                "Coord {" + std::to_string(new_coord.coordX) + "; " + std::to_string(new_coord.coordY) + "} is out of game field range!",
                Logger::Level::ERROR
            );

            throw WrongCheckerMoveException("Move is out of game field! ({" + std::to_string(new_coord.coordX) + 
                "; " + std::to_string(new_coord.coordY) + "})");
        }

        Player *current_player;

        switch (m_current_move){
            case CurrentMove::PLAYER_1:
                current_player = m_player_1.get();
                break;
            case CurrentMove::PLAYER_2:
                current_player = m_player_2.get();
                break;
        }

        try{
           current_player->make_move_to(old_coord, new_coord); 
        }
        catch(const WrongCheckerMoveException &error){
            Logger::do_log("GameCheckers::make_move_to (" + Logger::ptr_to_string(this) + ") throw WrongCheckerMoveException",
                Logger::Level::ERROR
            );

            throw error;
        }
    }

    void GameCheckers::change_turn(void){
        Logger::do_log("GameCheckers::change_turn called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);

        std::string log_current_turn;
        switch(m_current_move){
        case CurrentMove::PLAYER_1:
            m_current_move = CurrentMove::PLAYER_2;
            log_current_turn = "player_2";
            break;

        default:
            m_current_move = CurrentMove::PLAYER_1;
            log_current_turn = "player_1";
        }

        Logger::do_log("Current turn changed to " + log_current_turn, Logger::Level::INFO);
    }

    void GameCheckers::get_move_coord(Coord &old_coord, Coord &new_coord) const{
        Logger::do_log("GameCheckers::get_move_coord called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);

        std::cout << "Old checker coord (2 numbers): "; 
        std::cin >> old_coord.coordX >> old_coord.coordY;

        std::cout << "New checker coord (2 numbers): "; 
        std::cin >> new_coord.coordX >> new_coord.coordY;
    }

    void GameCheckers::output_current_turn_msg(void){
        Logger::do_log("GameCheckers::output_current_turn_msg called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);
        switch(m_current_move){
        case CurrentMove::PLAYER_1:
            std::wcout << L"Current turn: " << m_player_1->get_nickname();
            break;

        case CurrentMove::PLAYER_2:
            std::wcout << L"Current turn: " << m_player_2->get_nickname();
            break;

        default:
            m_current_move = CurrentMove::PLAYER_1;
        }

        Logger::do_log("Current turn outputed!", Logger::Level::TRACE);
    }
}