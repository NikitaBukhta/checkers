#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "checker.hpp"
#include "unright_color_exception.hpp"
#include "game_field.hpp"
#include "player_info.hpp"
#include "config.hpp"
#include "wrong_checker_move_exception.hpp"
#include "logger.hpp"

#include <deque>
#include <string>
#include <algorithm>
#include <memory>
#include <sstream>

namespace game{
    class Player : public PlayerInfo{
    private:
        std::deque<std::shared_ptr<Checker>> m_checkers;
        
    public:
        /* Description:
         * Default constructor of players;
         * Init count checkers based on GameField max checkers count from one side;
         */
        Player(const std::wstring nickname = L"Bot");

        Player(Color checkers_color, const std::wstring nickname = L"Bot");

        /* Description:
         *  Return player's checkers;
         *
         * Args:
         *  checkers - container is player's checkers will be written;
         */
        void get_checkers(std::deque<std::shared_ptr<Checker>> &checkers) const;

        /* Description:
         *  move checker to the new coord;
         *  Warning!!!
         *  method don't check if you move is right!
         *
         * Args:
         *  old_coord - old checker coord;
         *  new_coord - new checker coord;
         * 
         * Exceptions:
         *  Throw WrongCheckerMoveException if checker isn't found or move is impossible;
         */
        void make_move_to(const Coord &old_coord, const Coord &new_coord);

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

        bool checker_is_exists(const Coord &coord, Color color) const;

        bool checker_is_exists(const Coord &coord, Color color, std::deque<std::shared_ptr<Checker>>::const_iterator &checker_it) const;
    };
}

#endif // PLAYER_HPP