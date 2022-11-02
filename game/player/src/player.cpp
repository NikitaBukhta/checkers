#include "player.hpp"

namespace game{
    Player::Player(void){
        checkers.resize(GameField::get_max_checkers_count());
    }
}