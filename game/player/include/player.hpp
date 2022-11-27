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
#include <vector>
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

        void get_checker(const Coord &coord, std::unique_ptr<Checker> &checker) const;

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

        /* Description:
         *  Check if current player contains the checker;
         *
         * Args:
         *  coord - checker coord we want to find;
         * 
         * Return values:
         *  return true if player contains the checker;
         *  return false if not;
         */
        bool contain_checker(const Coord &coord) const;

        /* Description:
         *  remove checker from checker list with specific coord;
         *
         * Args:
         *  coord - specific coord where checker is;
         * 
         * Errors:
         *  throw std::out_of_range if no checkers found;
         */
        void remove_checker(const Coord &coord);

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

        /* Description:
         *  Check if current player contains the checker;
         *
         * Args:
         *  coord - checker coord we want to find;
         *  checker_it - written value to save current checker_it. Retured std::end(m_checkers)
         *      if checker was not found;
         * 
         * Return values:
         *  return true if player contains the checker;
         *  return false if not;
         */
        bool contain_checker(const Coord &coord, std::deque<std::shared_ptr<Checker>>::const_iterator &checker_it) const;
    };
}

#endif // PLAYER_HPP