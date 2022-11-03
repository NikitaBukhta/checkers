#include "player.hpp"

namespace game{
    Player::Player(const std::wstring nickname) : PlayerInfo(nickname){
        m_checkers.resize(config::START_CHECKERS_IN_ROW * config::START_ROWS_COUNT);
    }

    Player::Player(Color color, const std::wstring nickname) : Player(nickname){
        set_checkers_start_coord(color);
    }

    std::deque<Checker> Player::get_checkers(void) const{
        return m_checkers;
    }

    void Player::get_checkers(std::deque<Checker> &checkers) const{
        checkers = m_checkers;
    }

    void Player::set_checkers_start_coord(Color color){
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
                (*checker).set_color(color);
                (*checker).set_current_coord(Coord{column, row});

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
}