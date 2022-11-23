#include "game_field.hpp"

namespace game{
    Size GameField::get_game_field_size(void) noexcept{
        Logger::do_log("Logger::get_game_field_size (static). Returned: width: " + 
            std::to_string(m_GAME_FIELD_SIZE.width) + "; height: " + 
            std::to_string(m_GAME_FIELD_SIZE.height) + ";",
            Logger::Level::TRACE
        );

        return m_GAME_FIELD_SIZE;
    }

    void GameField::draw_game_field(void) const noexcept{
        Logger::do_log("GameField::draw_game_field (" + Logger::ptr_to_string(this) + ") called", Logger::Level::INFO);

        for(short row = m_GAME_FIELD_SIZE.height - 1; row >= 0; --row){
            for (short column = 0; column < m_GAME_FIELD_SIZE.width; ++column){
                std::cout << static_cast<int>(m_field[row][column]) << " ";
            }
            std::cout << std::endl;
        }
    }

    void GameField::add_checkers(const std::deque<std::shared_ptr<Checker>> &checkers){
        Logger::do_log("GameField::add_checkers (" + Logger::ptr_to_string(this) + ") called. Color: " +
            checkers[0]->color_to_string(), Logger::Level::INFO
        );

        Color checkers_color = checkers[0]->get_color();

        for(auto &checker : checkers){
            Coord current_checker_coord = checker->get_current_coord();

            m_field[current_checker_coord.coordY][current_checker_coord.coordX] = static_cast<int>(checkers_color) + static_cast<int>(checker->get_checker_type());
        }
    }

    void GameField::reset(void){
        Logger::do_log("GameField::reset called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO);

        m_field = {0};

        Logger::do_log("GameField cleared", Logger::Level::DEBUG);
    }

    bool GameField::coord_in_game_field(const Coord &coord) const noexcept{
        Logger::do_log("GameField::coord_in_game_field called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO);

        bool ret = false;

        ret = coord.coordX >= 0 && coord.coordX < m_GAME_FIELD_SIZE.width &&
            coord.coordY >= 0 && coord.coordY < m_GAME_FIELD_SIZE.height;

        Logger::do_log("GameField::coord_in_game_field (" + Logger::ptr_to_string(this) + 
            "). Returned: " + (ret ? "true" : "false"), Logger::Level::DEBUG
        );

        return ret;
    }
}