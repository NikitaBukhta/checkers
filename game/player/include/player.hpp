#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "checker.hpp"
#include "unright_color_exception.hpp"
#include "game_checkers.hpp"

#include <deque>
#include <string>

namespace game{
    class Player{
    private:
        std::deque<Checker> m_checkers;
        std::wstring m_nickname;
    public:
        /* Description:
         * Default constructor of players;s
         * Init count checkers based on GameField max checkers count from one side;
         */
        Player(void);

        Player(Color checkers_color, const std::wstring nickname = L"Bot");

        /* Description:
         *  Return player's nickname;
         */
        std::wstring get_nickname(void) const;

        /* Description:
         *  Return player's nickname;
         *
         * Args:
         *  nickname - container is player's nickname will be written;
         */
        void get_nickname(std::wstring &nickname) const;

        /* Description:
         *  Set new player nickname;
         */
        void set_nickname(const std::wstring &nickname);

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