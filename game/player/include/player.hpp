#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "checker.hpp"
#include "game_field.hpp"

#include <deque>
#include <string>

namespace game{
    class Player{
    private:
        std::deque<Checker> checkers;
        std::wstring nickname;
    public:
        /* Description:
         * Default constructor of players;
         * Init count checkers based on GameField max checkers count from one side;
         */
        Player(void);
    };
}

#endif // PLAYER_HPP