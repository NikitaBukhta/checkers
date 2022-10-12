#ifndef CHECKER_HPP
#define CHECKER_HPP

#include "ifigure.hpp"

namespace game{
    class Checker : public IFigure{
    private:
        Color m_color;
        Coord m_current_coord;
    public:
        Checker(Coord coord = {}, Color color = Color::white) : m_current_coord(coord), m_color(color) {}

        void make_move_to(const Coord &coord) override;

        Coord get_current_coord(void);
    };
}

#endif // !CHECKER_HPP