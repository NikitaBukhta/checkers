#include "player.hpp"

namespace game{
    Player::Player(const std::wstring nickname) : PlayerInfo(nickname){
        Logger::do_log("Player constructor called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);

        m_checkers.resize(config::START_CHECKERS_IN_ROW * config::START_ROWS_COUNT);
    }

    Player::Player(Color color, const std::wstring nickname) : Player(nickname){
        set_checkers_start_coord(color);
    }

    void Player::get_checkers(std::deque<std::shared_ptr<Checker>> &checkers) const{
        Logger::do_log("Player::get_checkers called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);
        size_t checkers_count = m_checkers.size();

        if(!checkers.empty()){
            checkers.clear();
        }
        checkers.resize(checkers_count);

        for (size_t i = 0; i < checkers_count; ++i){
            checkers[i].reset(new Checker(*m_checkers[i].get()));
            Logger::do_log("Checker #" + std::to_string(i) + " (" + Logger::ptr_to_string(&checkers[i]) 
                + ") color: " + checkers[i]->color_to_string() +
                "; Coord: {" + std::to_string(checkers[i]->get_current_coord().coordX) + "; " + 
                std::to_string(checkers[i]->get_current_coord().coordY) + "}", Logger::Level::DEBUG
            );
        }
    }

    void Player::set_checkers_start_coord(Color color){
        Logger::do_log("Player::set_checkers_start_coord (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);
        short start_row = 0;
        short start_rows_count = config::START_ROWS_COUNT;
        short start_checkers_in_row = config::START_CHECKERS_IN_ROW;
        
        // looking for start position for checkers
        // black from 5-th row, white from 1-st;
        switch (color)
        {
        case Color::WHITE:
            start_row = 0;
            break;

        case Color::BLACK:
            start_row = GameField::get_game_field_size().height - start_rows_count;
            break;
        
        default:
            Logger::do_log("Player::set_checkers_start_coord" + Logger::ptr_to_string(this) + "function throw the UnrightColorException",
                Logger::Level::ERROR
            );

            throw UnrightColorException("Undefined color!");
        }

        short row = start_row;
        short column;
        auto checker = std::begin(m_checkers);
        auto checker_end = std::end(m_checkers);
        for (; row < start_rows_count + start_row; ++row){
            if (row % 2 == 0){
                column = 0;
            }
            else{
                column = 1;
            }

            for (column; column < start_checkers_in_row * 2; column += 2){
                checker->reset(new Checker(Coord{column, row}, color));
                Logger::do_log("Set checker #" + std::to_string(start_checkers_in_row * (row - start_row) + column / 2) + 
                    " (" + Logger::ptr_to_string(&(*checker)) + ") color: " + 
                    (color == Color::WHITE ? "white" : "black") + "; Coord: {" + std::to_string(column) +
                    "; " + std::to_string(row) + "};", Logger::Level::DEBUG
                );

                // if no checkers left, end the loop;
                if (++checker == checker_end){
                    break;
                }
            }

            // approve break;
            if (checker == checker_end){
                break;
            }
        }
    }
    
    void Player::make_move_to(const Coord &old_coord, const Coord &new_coord){
        Logger::do_log("Player::make_move_to called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);

        std::deque<std::shared_ptr<Checker>>::const_iterator checker_it;
        // if needed checker is not exists;
        if (!checker_is_exists(old_coord, checker_it)){
            std::string error_msg = "Checker with coord {" + std::to_string(old_coord.coordX) + "; " + 
                std::to_string(old_coord.coordY) + "} and color " +
                m_checkers[0]->color_to_string() + " is not found!";

            Logger::do_log("Player::make_move_to (" + Logger::ptr_to_string(this) + ") function throw the WrongCheckerMoveException: " +
                error_msg, Logger::Level::ERROR
            );

            throw WrongCheckerMoveException(error_msg);
        }
        // if there is checker in new position
        else if(checker_is_exists(new_coord)){
            std::string error_msg = "Checker with coord {" + std::to_string(old_coord.coordX) + "; " + 
                std::to_string(old_coord.coordY) + "} and color " +
                m_checkers[0]->color_to_string() + " stayed at this position!";

            Logger::do_log("Player::make_move_to (" + Logger::ptr_to_string(this) + ") function throw the WrongCheckerMoveException: " +
                error_msg, Logger::Level::ERROR
            );
            
            throw WrongCheckerMoveException(error_msg);
        }
        
        try{
            (*checker_it)->make_move_to(new_coord);
        }
        catch(const WrongCheckerMoveException &error){
            Logger::do_log("Player::make_move_to (" + Logger::ptr_to_string(this) + ") function throw the WrongCheckerMoveException",
                Logger::Level::ERROR
            );
            
            throw error;
        }
    }

    bool Player::checker_is_exists(const Coord &coord) const{
        std::deque<std::shared_ptr<Checker>>::const_iterator temp_it;

        return checker_is_exists(coord, temp_it);
    }

    bool Player::checker_is_exists(const Coord &coord, std::deque<std::shared_ptr<Checker>>::const_iterator &checker_it) const{
        Logger::do_log("Player::checker_is_exists called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);

        // create temp checker to check if we have the such as;
        std::unique_ptr<Checker> needed_checker = std::make_unique<Checker>(Checker(coord, m_checkers[0]->get_color()));
        checker_it = std::find_if(std::begin(m_checkers), std::end(m_checkers), 
            [&](std::shared_ptr<Checker> obj){
                return *obj.get() == *needed_checker;
            }
        );

        bool ret = checker_it != std::end(m_checkers);

        Logger::do_log("Player::checker_is_exists (" + Logger::ptr_to_string(this) + ") returned: " +
            (ret ? "true" : "false"), Logger::Level::DEBUG
        );
        
        return ret;
    }
}