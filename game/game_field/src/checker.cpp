#include "checker.hpp"

namespace game{
    void Checker::make_move_to(const Coord &coord){
        m_current_coord = coord;
    }

    Coord Checker::get_current_coord(void){
        return m_current_coord;
    }
}