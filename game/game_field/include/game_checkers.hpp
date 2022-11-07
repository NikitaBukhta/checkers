#ifndef GAME_CHECKERS_HPP
#define GAME_CHECKERS_HPP

#include <memory>
#include <iostream>

#include "igame.hpp"
#include "checker.hpp"
#include "game_field.hpp"
#include "player.hpp"

namespace game{
    class GameCheckers : public IGame{

    private:
        GameField m_game_filed;

        std::unique_ptr<Player> player_1;
        std::unique_ptr<Player> player_2;

    public:
        GameCheckers(void);

        int start(void) override;

        /* Descriptions:
         *  Return count of rows with checkers at the start spawn;
         */
        static short get_start_rows_count(void) noexcept;
    };
}

#endif // !GAME_CHECKERS_HPP