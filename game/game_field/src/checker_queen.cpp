#include "checker_queen.hpp"

namespace game{
    bool CheckerQueen::operator== (const CheckerQueen &other) const{
        return Checker::operator==(other);
    }

    bool CheckerQueen::operator!= (const CheckerQueen &other) const{
        return Checker::operator!=(other);
    }

    void CheckerQueen::make_move_to(const Coord &coord){
        m_current_coord = coord;
        //dynamic_cast<this>(make_move_to(coord));
    }
}