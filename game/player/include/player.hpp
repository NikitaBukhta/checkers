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

        std::wstring get_nickname(void) const;

        void get_nickname(std::wstring &nickname) const;

        void set_nickname(const std::wstring &nickname);

        std::deque<Checker> get_checkers(void) const;

        void get_checkers(std::deque<Checker> &checkers) const;

    private:
        void set_checkers_start_coord(Color color);
    };
}

#endif // PLAYER_HPP