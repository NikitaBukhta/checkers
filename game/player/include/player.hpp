#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "checker.hpp"
#include "unright_color_exception.hpp"
#include "game_field.hpp"
#include "player_info.hpp"
#include "config.hpp"

#include <deque>
#include <string>

namespace game{
    class Player : public PlayerInfo{
    private:
        std::deque<Checker> m_checkers;
        
    public:
        /* Description:
         * Default constructor of players;s
         * Init count checkers based on GameField max checkers count from one side;
         */
        Player(const std::wstring nickname = L"Bot");

        Player(Color checkers_color, const std::wstring nickname = L"Bot");

        /* Description:
         *  Return player's checkers;
         */
        std::deque<Checker> get_checkers(void) const;

        /* Description:
         *  Return player's checkers;
         *
         * Args:
         *  checkers - container is player's checkers will be written;
         */
        void get_checkers(std::deque<Checker> &checkers) const;

    private:
        /* Description:
         *  Set start coord for checker, depends on that color;
         *   - White checkers start from {0; 0};
         *   - Black checkers start from 3-d line from end;
         *
         * Args:
         *  color - color of checkers we set;
         * 
         * Exceptions:
         *  Throw UnrightColorException if color is undefined;
         */
        void set_checkers_start_coord(Color color);
    };
}

#endif // PLAYER_HPP