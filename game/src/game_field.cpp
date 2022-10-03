#include "game_field.hpp"
#include "unright_color_exception.hpp"

namespace game{
    GameField::GameField(void){
        std::thread white_thread (&GameField::fill_checkers_field_with, this, Color::white);
        std::thread black_thread (&GameField::fill_checkers_field_with, this, Color::black);
        
        white_thread.join();
        black_thread.join();
    }

    Size GameField::get_game_field_size(void) noexcept{
        return m_GAME_FIELD_SIZE;
    }

    void GameField::draw_game_field(void) const noexcept{
        for(short row = m_GAME_FIELD_SIZE.height - 1; row >= 0; --row){
            for (short column = 0; column < m_GAME_FIELD_SIZE.width; ++column){
                std::cout << field[row][column] << " ";
            }
            std::cout << std::endl;
        }
    }

    void GameField::fill_checkers_field_with(Color checker_color){
        short start_row = 0;
        
        switch (checker_color)
        {
        case Color::white:
            start_row = 0;
            break;

        case Color::black:
            start_row = m_GAME_FIELD_SIZE.height - m_START_ROWS_COUNT;
            break;
        
        default:
            throw UnrightColorException("Undefined color!");
        }

        short row;
        short column;
        for (row = start_row; row < m_START_ROWS_COUNT + start_row; ++row){
            if (row % 2 == 0){
                column = 0;
            }
            else{
                column = 1;
            }

            for (column; column < m_START_CHECKERS_IN_ROW * 2; column += 2){
                field[row][column] = static_cast<int>(checker_color);
            }
        }
    }
}