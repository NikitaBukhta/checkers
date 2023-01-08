#ifndef GAME_CHECKERS_HPP
#define GAME_CHECKERS_HPP

#include <memory>
#include <iostream>
#include <thread>
#include <vector>
#include <cmath>

#include "igame.hpp"
#include "checker.hpp"
#include "game_field.hpp"
#include "player.hpp"
#include "logger.hpp"
#include "wrong_checker_move_exception.hpp"

namespace game{
    class GameCheckers : public IGame{

    private:
        enum class CurrentMove : char{
            PLAYER_1,
            PLAYER_2
        };

        enum class CurrentMoveDirection : char{
            LEFT_UP = 0,
            LEFT_DOWN,
            RIGHT_DOWN,
            RIGHT_UP
        };

        GameField m_game_filed;

        std::unique_ptr<Player> m_player_1;
        std::unique_ptr<Player> m_player_2;

        CurrentMove m_current_move;

        bool m_need_to_hit = false;

    public:
        GameCheckers(void);
        
        /* Description:
         *  This method start game checkers;
         */
        int start(void) override;

    private:
        /* Discription:
         *  Move checker from A to B coord;
         *
         * Args:
         *  old_coord - checker's first coord;
         *  new_coord - checker's new coord we move to;
         * 
         * Errors:
         *  Throw WrongCheckerMoveException if:
         *      * new coord is out of range;
         *      * checker wasn't found;
         *      * move is imposible;
         */
        void make_move_to(const Coord &old_coord, const Coord &new_coord);

        /* Description:
         *  Change current turn for players;
         */
        void change_turn(void);

        /* Description:
         *  Write in vars user input for moving the checker;
         *
         * Args:
         *  old_coord - checker's coord we want to move;
         *  new_coord - checker's new coord;
         */
        void get_move_coord(Coord &old_coord, Coord &new_coord) const;

        void get_checker_to_move(Coord &coord) const;

        void get_coord_move_to(Coord &coord) const;

        /* Description:
         *  Display current turn on the screen;
         */
        void output_current_turn_msg(void);

        /* Description:
         *  Check if there are enemies on the one line with checker we want to move;
         *
         * Args:
         *  checker_coord - checker we want to move;
         *  enemies_coord - list of all enemies are in line with our checker;
         * 
         * Return values:
         *  return true if enemies were found;
         *  return false if enemies were not found;
         */
        bool enemies_in_line(const Coord &checker_coord, std::vector<Coord> &enemies_coord) const;

        /* Description:
         *  move simple checker from A to B;
         *
         * Args:
         *  old_coord - old checker coord we want to move;
         *  new_coord - new checker coord we want to move;
         *  current_player - player making the current turn. Their checker we will move;
         * 
         * Errors:
         *  Throw WrongCheckerMoveException if move is impossible. You can read more information in errors details.
         */
        void move_simple_checker(const Coord &old_coord, const Coord &new_coord, Player *current_player);

        void move_queen_checker(const Coord &old_coord, const Coord &new_coord, Player *current_player);

        /* Description:
         *  Check which checkers must to hit;
         *
         * Args:
         *  checkers - writable value which will contain a checkers coord that could make a move.
         *      If checkers size is 0, no checkers can a kill the other;
         * 
         * Return values:
         *  return true if there are checkers that must to hit the other;
         *  return false if not;
         */
        bool checkers_need_to_hit(std::vector<Coord> &checkers) const;

        /* Description:
         *  remove checker from one player's checker list;
         *
         * Args:
         *  coord - coord of checker we want to KILL;
         */
        void kill_checker(const Coord &coord);

        bool check_for_queen(const Coord &checker_coord) const noexcept;
    };
}

#endif // !GAME_CHECKERS_HPP