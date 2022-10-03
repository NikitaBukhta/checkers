#ifndef GAME_CHECKERS_HPP
#define GAME_CHECKERS_HPP

#include <memory>
#include <iostream>

#include "igame.hpp"
#include "checker.hpp"
#include "game_field.hpp"

namespace game{
    class GameCheckers : public IGame{
    private:
        GameField m_game_filed;

    public:
        int start(void) override;
    };
}

#endif // !GAME_CHECKERS_HPP