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

        // check if coords are right;
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
            std::unique_ptr<Checker> moving_checker;
            current_player->get_checker(old_coord, moving_checker);

            if (moving_checker.get() == nullptr){
                throw WrongCheckerMoveException("");
            }
            
            switch(moving_checker->get_checker_type()){
                case CheckerType::CHECKER:
                    move_simple_checker(old_coord, new_coord, current_player);
                    // TODO: logic for moving checker with kill;
                    break;
                
                case CheckerType::QUEEN:
                    // TODO: logic for moving checker with kill;
                    break;
                
                default:
                    break;
            }
            //current_player->make_move_to(old_coord, new_coord); 
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
            std::wcout << L"Current turn: " << m_player_1->get_nickname() << std::endl;
            break;

        case CurrentMove::PLAYER_2:
            std::wcout << L"Current turn: " << m_player_2->get_nickname() << std::endl;
            break;

        default:
            m_current_move = CurrentMove::PLAYER_1;
        }

        Logger::do_log("Current turn outputed!", Logger::Level::TRACE);
    }

    bool GameCheckers::enemies_in_line(const Coord &checker_coord, std::vector<Coord> &enemies_coord) const{
        Logger::do_log("GameCheckers::enemies_in_line called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);
        enemies_coord.clear();
        
        Player *enemy;
        
        switch (m_current_move){
            case CurrentMove::PLAYER_1:
                enemy = m_player_2.get();
                Logger::do_log("GameCheckers::enemies_in_line current enemy player_2 (" + Logger::ptr_to_string(enemy) + ")",
                    Logger::Level::INFO
                );

                break;

            case CurrentMove::PLAYER_2:
                enemy = m_player_1.get();
                Logger::do_log("GameCheckers::enemies_in_line current enemy player_1 (" + Logger::ptr_to_string(enemy) + ")",
                    Logger::Level::INFO
                );

                break;

            default:
                std::string error_msg = "No player found";
                Logger::do_log("GameCheckers::enemies_in_line throw the WrongCheckerMoveException. " + error_msg,
                    Logger::Level::ERROR
                );

                throw WrongCheckerMoveException(error_msg);
        }

        // lambda that move coord by one to the one of sides;
        auto move_coord = [](Coord &coord, CurrentMoveDirection direction){
            switch(direction){
                case CurrentMoveDirection::LEFT_DOWN:
                    --coord.coordX;
                    --coord.coordY;
                    break;

                case CurrentMoveDirection::LEFT_UP:
                    --coord.coordX;
                    ++coord.coordY;
                    break;

                case CurrentMoveDirection::RIGHT_DOWN:
                    ++coord.coordX;
                    --coord.coordY;
                    break;

                case CurrentMoveDirection::RIGHT_UP:
                    ++coord.coordX;
                    ++coord.coordY;
                    break;
            }
        };

        char sides_count = 4;
        // check every side for enemies;
        for (char i = 0; i < sides_count; ++i){
            // go to the start position;
            Coord checked_coord = checker_coord;
            do{
                move_coord(checked_coord, static_cast<CurrentMoveDirection>(i));
                Logger::do_log("GameCheckers::enemies_in_line checked coord: " + checked_coord.to_string(), Logger::Level::DEBUG);
                if (enemy->contain_checker(checked_coord)){
                    enemies_coord.push_back(checked_coord);
                    Logger::do_log("GameCheckers::enemies_in_line added new enemy checker with coord: {" +
                        std::to_string(checked_coord.coordX) + "; " + std::to_string(checked_coord.coordY) + "}",
                        Logger::Level::DEBUG
                    );
                }
            // if we go to the end of game field, go to the next side;
            }while(m_game_filed.coord_in_game_field(checked_coord));
        }

        return enemies_coord.size() != 0;
    }

    void GameCheckers::move_simple_checker(const Coord &old_coord, const Coord &new_coord, Player *current_player){
        std::vector<Coord> enemies;
        Coord distance = new_coord - old_coord;
        Coord distance_module = {static_cast<short>(std::abs(distance.coordX)), static_cast<short>(std::abs(distance.coordY))};
        Coord max_checker_distance_to_move = Checker::get_max_distance_to_move();
        enemies_in_line(old_coord, enemies);
        // if there is right distance to move;
        if (distance_module == max_checker_distance_to_move){
            if (std::find(std::begin(enemies), std::end(enemies), new_coord) == std::end(enemies)){
                try{
                    switch(m_current_move){
                        case CurrentMove::PLAYER_1:
                            if (distance.coordY != 1){
                                throw WrongCheckerMoveException("The checker cannot go back!");
                            }
                            break;

                        case CurrentMove::PLAYER_2:
                            if (distance.coordY != -1){
                                throw WrongCheckerMoveException("The checker cannot go back!");
                            }
                            break; 
                    }
                    current_player->make_move_to(old_coord, new_coord);
                }
                catch(const WrongCheckerMoveException &error){
                    throw error;
                }
            }
            else{
                std::string error_msg;

                throw WrongCheckerMoveException(error_msg);
            }
        }
        else if (distance_module == (max_checker_distance_to_move * 2)){
            Coord enemy_coord = old_coord + (distance / 2);

            if(enemies_in_line(old_coord, enemies)){
                if (std::find(std::begin(enemies), std::end(enemies), new_coord) == std::end(enemies) &&
                    std::find(std::begin(enemies), std::end(enemies), enemy_coord) != std::end(enemies))
                {
                    try{
                        current_player->make_move_to(old_coord, enemy_coord);
                        current_player->make_move_to(enemy_coord, new_coord);
                        // TODO: kill!
                    }
                    catch(const WrongCheckerMoveException &error){
                        current_player->make_move_to(enemy_coord, old_coord);
                        throw error;
                    }
                }
                else{
                    std::string error_msg;

                    throw WrongCheckerMoveException(error_msg);
                }
            }
            else{
                std::string error_msg;

                throw WrongCheckerMoveException(error_msg);
            }
        }
        else{
            std::string error_msg;

            throw WrongCheckerMoveException(error_msg);
        }
    }
}