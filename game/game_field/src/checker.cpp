#include "checker.hpp"

namespace game{
    void Checker::make_move_to(const Coord &coord){
        m_current_coord = coord;
    }

    Coord Checker::get_current_coord(void) const{
        return m_current_coord;
    }

    void Checker::set_current_coord(const Coord &coord){
        m_current_coord = coord;
    }

    Color Checker::get_color(void) const noexcept{
        return m_color;
    }

    void Checker::set_color(Color color) noexcept{
        m_color = color;
    }
}