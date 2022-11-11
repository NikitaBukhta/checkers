#include "game_field.hpp"

namespace game{
    Size GameField::get_game_field_size(void) noexcept{
        Logger::do_log("Logger::get_game_field_size (static). Returned: width: " + 
            std::to_string(m_GAME_FIELD_SIZE.width) + "; height: " + 
            std::to_string(m_GAME_FIELD_SIZE.height) + ";"
        );

        return m_GAME_FIELD_SIZE;
    }

    void GameField::draw_game_field(void) const noexcept{
        Logger::do_log("GameField::draw_game_field (" + Logger::ptr_to_string(this) + ") called", Logger::Level::TRACE);

        for(short row = m_GAME_FIELD_SIZE.height - 1; row >= 0; --row){
            for (short column = 0; column < m_GAME_FIELD_SIZE.width; ++column){
                std::cout << static_cast<int>(m_field[row][column]) << " ";
            }
            std::cout << std::endl;
        }
    }

    void GameField::add_checkers(const std::deque<std::shared_ptr<Checker>> &checkers){
        Logger::do_log("GameField::add_checkers (" + Logger::ptr_to_string(this) + ") called. Color: " +
            (checkers[0]->get_color() == Color::WHITE ? "white" : "black"), Logger::Level::TRACE
        );

        Color checkers_color = checkers[0]->get_color();

        for(auto &checker : checkers){
            Coord current_checker_coord = checker->get_current_coord();
            m_field[current_checker_coord.coordY][current_checker_coord.coordX] = checkers_color;
        }
    }
}