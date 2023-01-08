#include "game_checkers.hpp"

namespace game{
    GameCheckers::GameCheckers(void){
        std::thread(&Logger::do_log, "GameCheckers constructor called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();

        m_player_1.reset(new Player(Color::WHITE, L"Player_1"));
        m_player_2.reset(new Player(Color::BLACK, L"Player_2"));

        m_current_move = CurrentMove::PLAYER_1;
    }

    int GameCheckers::start(void){
        std::thread(&Logger::do_log, "GameCheckers::start called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();

        std::deque<std::shared_ptr<Checker>> player_1_checkers;
        std::deque<std::shared_ptr<Checker>> player_2_checkers;

        m_player_2->change_checker_type(Coord{1, 5}, CheckerType::QUEEN);
        m_player_1->change_checker_type(Coord{0, 2}, CheckerType::QUEEN);

        Coord old_coord;
        Coord new_coord;

        std::vector<Coord> checkers_must_move;

        bool repeat_player_move = false;
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

            m_need_to_hit = checkers_need_to_hit(checkers_must_move);

            // while right move is not completed;
            while (true){
                try{
                    if (repeat_player_move){
                        old_coord = new_coord;
                        get_coord_move_to(new_coord);
                    }
                    else{
                        get_move_coord(old_coord, new_coord);
                    }

                    // if there is checker that must to hit;
                    if (m_need_to_hit){
                        // if the current checker cannot to hit;
                        if (std::find(std::begin(checkers_must_move), std::end(checkers_must_move), old_coord) == std::end(checkers_must_move)){
                            std::string error_msg = "Hit is neccessary!";

                            std::thread (&Logger::do_log, "GameChecker::start (" + Logger::ptr_to_string(this) + ") throw the WrongCheckerMoveException: " + error_msg,
                                Logger::Level::ERROR
                            ).detach();

                            throw WrongCheckerMoveException(error_msg);
                        }

                        make_move_to(old_coord, new_coord);
                        checkers_must_move.clear();

                        if (checkers_need_to_hit(checkers_must_move)){
                            Logger::do_log("GameCheckers::start (" + Logger::ptr_to_string(this) + "). Check if additional hit is neccessary!", Logger::Level::DEBUG);
                            repeat_player_move = std::find(std::begin(checkers_must_move), std::end(checkers_must_move), new_coord) != std::end(checkers_must_move);

                            size_t i = 0;
                            for (auto &checker_it : checkers_must_move){
                                Logger::do_log("GameCheckers::start (" + Logger::ptr_to_string(this) + "). Checker must hit #" 
                                    + std::to_string(i++) + ": coord = " + checker_it.to_string(), Logger::Level::DEBUG)
                                ;
                            }
                        }
                        else{
                            Logger::do_log("GameCheckers::start (" + Logger::ptr_to_string(this) + "). Additional hit isn't neccessary!", Logger::Level::DEBUG);
                            repeat_player_move = false;
                        }
                        //check_for_repeat_move_th.join();
                    }
                    else{
                        make_move_to(old_coord, new_coord);
                    }

                    break;
                }
                catch(const WrongCheckerMoveException &error){
                    std::cerr << error.what() << std::endl << "Please, try again!" << std::endl;
                    // TODO: REMOVE THESE LINES IN RELEASE!
                    // TEMP! FOR CONSOLE DEBUG;
                    m_game_filed.draw_game_field();
                    output_current_turn_msg();
                }
            }
            
            if (!repeat_player_move){
                checkers_must_move.clear();
                change_turn();
            }
        }

        return 0;
    }
    
    void GameCheckers::make_move_to(const Coord &old_coord, const Coord &new_coord){
        std::thread(&Logger::do_log, "GameCheckers::make_move_to called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();

        // check if coords are right;
        if (!m_game_filed.coord_in_game_field(new_coord)){
            std::string error_msg = "Move is out of game field range! Move coord: " + new_coord.to_string();

            std::thread(&Logger::do_log, "GameCheckers::make_move_to (" + Logger::ptr_to_string(this) + ") throw WrongCheckerMoveException" +
                error_msg, Logger::Level::ERROR
            ).detach();

            throw WrongCheckerMoveException(error_msg);
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
                    break;
                
                case CheckerType::QUEEN:
                    move_queen_checker(old_coord, new_coord, current_player);
                    break;
                
                default:
                    break;
            }
            //current_player->make_move_to(old_coord, new_coord); 
        }
        catch(const WrongCheckerMoveException &error){
            std::thread(&Logger::do_log, "GameCheckers::make_move_to (" + Logger::ptr_to_string(this) + ") throw WrongCheckerMoveException",
                Logger::Level::ERROR
            ).detach();

            throw error;
        }

        if (check_for_queen(new_coord)){
            current_player->change_checker_type(new_coord, CheckerType::QUEEN);
        }
    }

    void GameCheckers::change_turn(void){
        std::thread(&Logger::do_log, "GameCheckers::change_turn called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();

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

        std::thread(&Logger::do_log, "Current turn changed to " + log_current_turn, Logger::Level::INFO).detach();
    }

    void GameCheckers::get_move_coord(Coord &old_coord, Coord &new_coord) const{
        // TODO: change join to detach when logic changed to get pckg instead of console;
        std::thread(&Logger::do_log, "GameCheckers::get_move_coord called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).join();

        get_checker_to_move(old_coord);

        get_coord_move_to(new_coord);
    }

    void GameCheckers::get_checker_to_move(Coord &coord) const{
        std::cout << "Old checker coord (2 numbers): "; 
        std::cin >> coord.coordX >> coord.coordY;
    }

    void GameCheckers::get_coord_move_to(Coord &coord) const{
        std::cout << "New checker coord (2 numbers): "; 
        std::cin >> coord.coordX >> coord.coordY;
    }

    void GameCheckers::output_current_turn_msg(void){
        std::thread(&Logger::do_log, "GameCheckers::output_current_turn_msg called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();
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

        std::thread(&Logger::do_log, "Current turn outputed!", Logger::Level::TRACE).detach();
    }

    bool GameCheckers::enemies_in_line(const Coord &checker_coord, std::vector<Coord> &enemies_coord) const{
        std::thread(&Logger::do_log, "GameCheckers::enemies_in_line called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();
        enemies_coord.clear();
        
        Player *enemy;
        
        switch (m_current_move){
            case CurrentMove::PLAYER_1:
                enemy = m_player_2.get();
                std::thread(&Logger::do_log, "GameCheckers::enemies_in_line current enemy player_2 (" + Logger::ptr_to_string(enemy) + ")",
                    Logger::Level::INFO
                ).detach();

                break;

            case CurrentMove::PLAYER_2:
                enemy = m_player_1.get();
                std::thread(&Logger::do_log, "GameCheckers::enemies_in_line current enemy player_1 (" + Logger::ptr_to_string(enemy) + ")",
                    Logger::Level::INFO
                ).detach();

                break;

            default:
                std::string error_msg = "No player found";
                std::thread(&Logger::do_log, "GameCheckers::enemies_in_line throw the WrongCheckerMoveException. " + error_msg,
                    Logger::Level::ERROR
                ).detach();

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
                std::thread(&Logger::do_log, "GameCheckers::enemies_in_line checked coord: " + checked_coord.to_string(), Logger::Level::DEBUG).detach();
                if (enemy->contain_checker(checked_coord)){
                    enemies_coord.push_back(checked_coord);
                    std::thread(&Logger::do_log, "GameCheckers::enemies_in_line added new enemy checker with coord: " + checked_coord.to_string(),
                        Logger::Level::DEBUG
                    ).detach();
                }
            // if we go to the end of game field, go to the next side;
            }while(m_game_filed.coord_in_game_field(checked_coord));
        }

        return enemies_coord.size() != 0;
    }

    void GameCheckers::move_simple_checker(const Coord &old_coord, const Coord &new_coord, Player *current_player){
        std::thread(&Logger::do_log, "GameCheckers::move_simple_checker called (" + Logger::ptr_to_string(this), Logger::Level::INFO).detach();

        std::string error_msg;
        
        std::vector<Coord> enemies;
        Coord distance = new_coord - old_coord;
        Coord distance_module = {static_cast<short>(std::abs(distance.coordX)), static_cast<short>(std::abs(distance.coordY))};
        Coord max_checker_distance_to_move = Checker::get_max_distance_to_move();
        enemies_in_line(old_coord, enemies);

        // if there is right distance to move and we haven't to hit;
        if (distance_module == max_checker_distance_to_move && !m_need_to_hit){
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
                    error_msg = error.what();

                    std::thread(&Logger::do_log, "GameCheckers::move_simple_checker (" + Logger::ptr_to_string(this) + " throw the WrongChecjerMoveException: "+
                        error_msg, Logger::Level::ERROR
                    ).detach();

                    throw error;
                }
            }
            else{
                error_msg = "There is an enemy checker in coord " + new_coord.to_string();

                std::thread(&Logger::do_log, "GameCheckers::move_simple_checker (" + Logger::ptr_to_string(this) + " throw the WrongChecjerMoveException: "+
                    error_msg, Logger::Level::ERROR
                ).detach();

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
                        std::thread moving_th([&](){
                            current_player->make_move_to(old_coord, enemy_coord);
                            current_player->make_move_to(enemy_coord, new_coord);
                        });
                        
                        std::thread(&GameCheckers::kill_checker, this, enemy_coord).join();
                        moving_th.join();
                    }
                    catch(const WrongCheckerMoveException &error){
                        current_player->make_move_to(enemy_coord, old_coord);

                        std::string error_msg = error.what();

                        std::thread(&Logger::do_log, "GameCheckers::move_simple_checker (" + Logger::ptr_to_string(this) + " throw the WrongChecjerMoveException: "+
                            error_msg, Logger::Level::ERROR
                        ).detach();

                        throw error;
                    }
                }
                else{
                    error_msg = "There is checker on " + new_coord.to_string() + ", or/and enemy on " + enemy_coord.to_string() + " does not exist!";

                    std::thread(&Logger::do_log, "GameCheckers::move_simple_checker (" + Logger::ptr_to_string(this) + " throw the WrongChecjerMoveException: "+
                        error_msg, Logger::Level::ERROR
                    ).detach();

                    throw WrongCheckerMoveException(error_msg);
                }
            }
            else{
                error_msg = "There isn't enemies you can kill!";

                std::thread(&Logger::do_log, "GameCheckers::move_simple_checker (" + Logger::ptr_to_string(this) + " throw the WrongChecjerMoveException: "+
                    error_msg, Logger::Level::ERROR
                ).detach();

                throw WrongCheckerMoveException(error_msg);
            }
        }
        else{
            error_msg = "Impossible move for checker!";

            std::thread(&Logger::do_log, "GameCheckers::move_simple_checker (" + Logger::ptr_to_string(this) + " throw the WrongChecjerMoveException: "+
                error_msg, Logger::Level::ERROR
            ).detach();

            throw WrongCheckerMoveException(error_msg);
        }
    }

    void GameCheckers::move_queen_checker(const Coord &old_coord, const Coord &new_coord, Player* current_player){
        std::thread(&Logger::do_log, "GameCheckers::move_queen_checker called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();

        if (!m_game_filed.coord_in_game_field(new_coord)){
            std::string error_msg = "No right move coord! " + new_coord.to_string();
            
            std::thread(&Logger::do_log, "GameCheckers::move_queen_checker (" + Logger::ptr_to_string(this) 
                + ") throw the WrongCheckerMoveException: " + error_msg, Logger::Level::ERROR
            ).detach();

            throw WrongCheckerMoveException(error_msg); 
        }

        std::vector<Coord> enemies;
        if(enemies_in_line(old_coord, enemies)){
            bool can_hit = false;

            // sort to the closest enemy;
            std::sort(std::begin(enemies), std::end(enemies), 
                [&old_coord](const Coord &first, const Coord &second){
                    short dist_1 = std::sqrt(std::pow(old_coord.coordX - first.coordX, 2) + std::pow(old_coord.coordY - first.coordY, 2));
                    short dist_2 = std::sqrt(std::pow(old_coord.coordX - second.coordX, 2) + std::pow(old_coord.coordY - second.coordY, 2));

                    return dist_1 < dist_2;
                }
            );

            for (const auto &enemy_it : enemies){
                std::thread(&Logger::do_log, "GameCheckers::move_queen_checker (" + Logger::ptr_to_string(this) + 
                    "). Enemy coord: " + enemy_it.to_string(), Logger::Level::DEBUG
                ).detach();   
            }

            // check if new_coord and enemy_coord in one way;
            auto one_way_enemy_it = std::find_if(std::begin(enemies), std::end(enemies),
                [&old_coord, &new_coord](const Coord &enemy_coord){
                    Coord move_distance = old_coord - new_coord;
                    Coord distance_to_enemy = old_coord - enemy_coord;
                    return move_distance.coordX * distance_to_enemy.coordX > 0 && 
                        move_distance.coordY * distance_to_enemy.coordY > 0;
                }
            );

            if (m_need_to_hit){
                if (one_way_enemy_it != std::end(enemies)){
                    Coord steps;
                    {
                        Coord distance = {
                            static_cast<short>(one_way_enemy_it->coordX - old_coord.coordX),
                            static_cast<short>(one_way_enemy_it->coordY - old_coord.coordY)
                        };

                        steps = {
                            distance.coordX > 0 ? short(1) : short(-1),
                            distance.coordY > 0 ? short(1) : short(-1)
                        };
                    }

                    Coord defence = {
                        static_cast<short>(one_way_enemy_it->coordX + steps.coordX),
                        static_cast<short>(one_way_enemy_it->coordY + steps.coordY)
                    };
                    Coord team_checkers_coord = {
                        static_cast<short>(one_way_enemy_it->coordX - steps.coordX),
                        static_cast<short>(one_way_enemy_it->coordY - steps.coordY)
                    };

                    // TODO: multithreading;
                    if (std::find(std::begin(enemies), std::end(enemies), defence) == std::end(enemies) && !current_player->contain_checker(team_checkers_coord)){
                        // check for defence;
                        while (defence != new_coord){
                            defence = Coord{
                                static_cast<short>(defence.coordX + steps.coordX),
                                static_cast<short>(defence.coordY + steps.coordY)
                            };

                            std::thread(&Logger::do_log, "GameField::move_queen_checker (" + Logger::ptr_to_string(this) + 
                                "). Checked defence coord: " + defence.to_string(), Logger::Level::DEBUG
                            ).detach();

                            if (std::find(std::begin(enemies), std::end(enemies), defence) != std::end(enemies)){
                                std::string error_msg = "Impossible move! You cannot go throw the enemy!";

                                std::thread(&Logger::do_log, "GameCheckers::move_queen_checker (" + Logger::ptr_to_string(this) 
                                    + ") throw the WrongCheckerMoveException: " + error_msg, Logger::Level::ERROR
                                ).detach();

                                throw WrongCheckerMoveException(error_msg);
                            }
                        }

                        // check for teamates;
                        while (team_checkers_coord != old_coord){
                            defence = Coord{
                                static_cast<short>(defence.coordX - steps.coordX),
                                static_cast<short>(defence.coordY - steps.coordY)
                            };

                            std::thread(&Logger::do_log, "GameField::move_queen_checker (" + Logger::ptr_to_string(this) + 
                                "). Checked team coord: " + defence.to_string(), Logger::Level::DEBUG
                            ).detach();

                            if (current_player->contain_checker(team_checkers_coord)){
                                std::string error_msg = "Impossible move! You cannot go throw your teamate!";

                                std::thread(&Logger::do_log, "GameCheckers::move_queen_checker (" + Logger::ptr_to_string(this) 
                                    + ") throw the WrongCheckerMoveException: " + error_msg, Logger::Level::ERROR
                                ).detach();

                                throw WrongCheckerMoveException(error_msg);
                            }
                            
                        }
                        
                        std::thread move_checker_th(&Player::make_move_to, current_player, std::ref(old_coord), std::ref(new_coord));
                        std::thread(&GameCheckers::kill_checker, this, std::ref(*one_way_enemy_it)).join();
                        move_checker_th.join();
                    }
                    else{
                        std::string error_msg = "Checker is under defence! Try to hit the other! (hit is neccessary)";

                        std::thread(&Logger::do_log, "GameCheckers::move_queen_checker (" + Logger::ptr_to_string(this) 
                            + ") throw the WrongCheckerMoveException: " + error_msg, Logger::Level::ERROR
                        ).detach();

                        throw WrongCheckerMoveException(error_msg);
                    }
                }
                else{
                    std::string error_msg = "Hit is neccessary!";

                    std::thread(&Logger::do_log, "GameCheckers::move_queen_checker (" + Logger::ptr_to_string(this) 
                        + ") throw the WrongCheckerMoveException: " + error_msg, Logger::Level::ERROR
                    ).detach();

                    throw WrongCheckerMoveException(error_msg);
                }
            }
            else{
                if (one_way_enemy_it != std::end(enemies)){
                    Coord move_distance = old_coord - new_coord;
                    Coord distance_to_enemy = old_coord - *one_way_enemy_it;
                    
                    // if we don't move throw the enemy;
                    if (std::abs(move_distance.coordX) < std::abs(distance_to_enemy.coordX)){
                        current_player->make_move_to(old_coord, new_coord);
                    }
                    else{
                        std::string error_msg = "Impossible move! You cannot go throw the enemy!";

                        std::thread(&Logger::do_log, "GameCheckers::move_queen_checker (" + Logger::ptr_to_string(this) 
                            + ") throw the WrongCheckerMoveException: " + error_msg, Logger::Level::ERROR
                        ).detach();

                        throw WrongCheckerMoveException(error_msg);
                    }
                }
                else{
                    current_player->make_move_to(old_coord, new_coord);
                }
            }
        }
        else{
            current_player->make_move_to(old_coord, new_coord);
        }
    }

    // TODO: try to do optimization;
    bool GameCheckers::checkers_need_to_hit(std::vector<Coord> &checkers) const{
        std::thread(&Logger::do_log, "GameCheckers::checkers_need_to_hit called (" + Logger::ptr_to_string(this), Logger::Level::INFO).detach();

        Player *current_player;
        Player *enemy_player;

        switch(m_current_move){
            case CurrentMove::PLAYER_1:
                current_player = m_player_1.get();
                enemy_player = m_player_2.get();
                break;
            
            case CurrentMove::PLAYER_2:
                current_player = m_player_2.get();
                enemy_player = m_player_2.get();
                break;
        }
        
        std::deque<std::shared_ptr<Checker>> current_checkers;  // all checkers that can be moved;
        current_player->get_checkers(current_checkers);

        /* Description:
         * check if enemy_checker is under defence;
         *
         * Args:
         *  current_checker - checker that we move;
         *  enemy_checker - checker we want to kill;
         *  begin - begin of enemies array;
         *  end - end of enemies array;
         * 
         * Return values:
         *  return true if defence was found;
         *  return false if not;
         */
        auto check_for_defence = [&current_checkers, this](Coord current_checker, Coord enemy_checker, auto begin, auto end){
            Coord distance = enemy_checker - current_checker;

            Coord defence_coord = Coord{
                distance.coordX > 0 ? static_cast<short>(enemy_checker.coordX + 1) : static_cast<short>(enemy_checker.coordX - 1),
                distance.coordY > 0 ? static_cast<short>(enemy_checker.coordY + 1) : static_cast<short>(enemy_checker.coordY - 1)
            };

            // if checker on the edge, is under defence!
            if (!m_game_filed.coord_in_game_field(defence_coord)){
                return true;
            }

            std::thread(&Logger::do_log, "GameCheckers::checkers_need_to_hit::check_for_defence (" + Logger::ptr_to_string(this) + 
                "). Current checker: " + current_checker.to_string() + ", enemy checker: " + enemy_checker.to_string() + 
                ", distance: " + distance.to_string() + ", defence coord = " + defence_coord.to_string(), Logger::Level::DEBUG    
            ).detach();

            return std::find(begin, end, defence_coord) != end || 
                std::find_if(std::begin(current_checkers), std::end(current_checkers), 
                    [&defence_coord](auto checker){ 
                        return checker->get_current_coord() == defence_coord;
                    }
                ) != std::end(current_checkers);
        };

        Coord game_field_edge;
        {
            Size game_field_size = m_game_filed.get_game_field_size();
            game_field_edge = Coord{static_cast<short>(game_field_size.width - 1), static_cast<short>(game_field_size.height)};
        }

        std::vector<Coord> temp_enemies_coord_vector;
        for (auto checker_it : current_checkers){
            temp_enemies_coord_vector.clear();
            enemies_in_line(checker_it->get_current_coord(), temp_enemies_coord_vector);

            for (auto enemy_coord_it = std::begin(temp_enemies_coord_vector); enemy_coord_it != std::end(temp_enemies_coord_vector); ++enemy_coord_it){
                // check if we checker isn't in the game field edge;
                if (enemy_coord_it->coordX == 0 || enemy_coord_it->coordY == 0 || 
                    enemy_coord_it->coordX == game_field_edge.coordX || enemy_coord_it->coordY == game_field_edge.coordY
                    )
                {
                    continue;
                }
                
                if (checker_it->get_checker_type() == CheckerType::CHECKER){
                    Coord distance = checker_it->get_current_coord() - *enemy_coord_it;
                    Coord distance_mod = {static_cast<short>(std::abs(distance.coordX)), static_cast<short>(std::abs(distance.coordY))};

                    // check if we can hit;
                    if (distance_mod.coordX != 1 || distance_mod.coordY != 1){
                        continue;
                    }
                }
                else{
                    Coord current_checker_coord = checker_it->get_current_coord();
                    Coord distance =  current_checker_coord - *enemy_coord_it;
                    Coord steps = {
                        distance.coordX > 0 ? short(1) : short(-1),
                        distance.coordY > 0 ? short(1) : short(-1)
                    };

                    Coord checked_coord = *enemy_coord_it;
                    
                    bool teamate_detected = false;
                    while (checked_coord != current_checker_coord){
                        checked_coord = checked_coord + steps;

                        if (current_player->contain_checker(checked_coord)){
                            teamate_detected = true;
                            break;
                        }
                    }

                    if (teamate_detected){
                        continue;
                    }
                }

                // check if checker is under defence;
                auto hit_checker = enemy_coord_it;
                std::thread(&Logger::do_log, "GameCheckers::checkers_need_to_hit (" + Logger::ptr_to_string(this) + 
                    "). Checked defence coord for " + hit_checker->to_string(), Logger::Level::DEBUG).detach();
                if (!check_for_defence(checker_it->get_current_coord(), *hit_checker, ++enemy_coord_it, std::end(temp_enemies_coord_vector))){
                    checkers.push_back(checker_it->get_current_coord());
                    enemy_coord_it = hit_checker;   // return iterator back;

                    break;
                }

                enemy_coord_it = hit_checker;   // return iterator back;
            }
        }

        std::thread(&Logger::do_log, "GameCheckers::checkers_need_to_hit (" + Logger::ptr_to_string(this) + 
            "). Checkers.size() = " + std::to_string(checkers.size()),
            Logger::Level::DEBUG    
        ).detach();

        size_t i = 0;
        for (auto enemies_coord_it : checkers){
            std::thread(&Logger::do_log, "GameCheckers::checkers_need_to_hit (" + Logger::ptr_to_string(this) + 
                ". Checker #" + std::to_string(i++) + " coord: " + enemies_coord_it.to_string(),
                Logger::Level::DEBUG
            ).detach();
        }

        return checkers.size() != 0;
    }

    void GameCheckers::kill_checker(const Coord &coord){
        std::thread(&Logger::do_log, "GameCheckers::kill_checker called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();

        Player *enemy_player;

        std::thread(&Logger::do_log, "GameCheckers::kill_checker (" + Logger::ptr_to_string(this) + 
            ". Current_move: " + (m_current_move == CurrentMove::PLAYER_1 ? "player_1" : "player_2"),
            Logger::Level::DEBUG
        ).detach();

        switch(m_current_move){
            case CurrentMove::PLAYER_1:
                enemy_player = m_player_2.get();
                break;

            case CurrentMove::PLAYER_2:
                enemy_player = m_player_1.get();
                break;
        }

        enemy_player->remove_checker(coord);
    }

    bool GameCheckers::check_for_queen(const Coord &coord) const noexcept{
        std::thread(&Logger::do_log, "GameChecker::check_for_queen called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE).detach();

        short first_row_number = 0;
        short last_row_number = m_game_filed.get_game_field_size().height - 1;

        switch(m_current_move){
            case CurrentMove::PLAYER_1:
                return coord.coordY == last_row_number;
            
            case CurrentMove::PLAYER_2:
                return coord.coordY == first_row_number;

            default:
                return false;
        }
    }
}