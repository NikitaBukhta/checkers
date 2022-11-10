#ifndef GAME_CHECKERS_HPP
#define GAME_CHECKERS_HPP

#include <memory>
#include <iostream>

#include "igame.hpp"
#include "checker.hpp"
#include "game_field.hpp"
#include "player.hpp"
#include "logger.hpp"

namespace game{
    class GameCheckers : public IGame{

    private:
        enum class CurrentMove : char{
            PLAYER_1,
            PLAYER_2
        };

        GameField m_game_filed;

        std::unique_ptr<Player> m_player_1;
        std::unique_ptr<Player> m_player_2;

        CurrentMove m_current_move;

    public:
        GameCheckers(void);

        int start(void) override;

    private:
        void make_move_to(const Coord &old_coord, const Coord &new_coord);
    };
}

#endif // !GAME_CHECKERS_HPP