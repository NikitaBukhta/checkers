#ifndef CHECKER_HPP
#define CHECKER_HPP

#include "ifigure.hpp"
#include "wrong_checker_move_exception.hpp"
#include "logger.hpp"

#include <cmath>
#include <string>

namespace game{
    class Checker : public IFigure{
    private:
        Color m_color;
        Coord m_current_coord;
    public:
        Checker(Coord coord = {}, Color color = Color::NO_COLOR) : m_current_coord(coord), m_color(color) {}

        Checker(const Checker &other);

        bool operator== (const Checker &other);

        bool operator!= (const Checker &other);

        /* Descriptions:
         *  Move checker to the specific coord;
         *
         * Args:
         *  coord - new checker coord;
         * 
         * Exceptions:
         *  Throw the WrongCheckerMoveException if distance from old to new coord more than (1; 1);
         */
        void make_move_to(const Coord &coord) override;

        /* Descriptions:
         *  Return current coord of checker;
         */
        Coord get_current_coord(void) const;

        /* Description:
         *  Set new coord for checker;
         *
         * Args:
         *  coord - new checker's coord;
         */
        void set_current_coord(const Coord &coord);

        /* Description:
         *  Return checker's color;
         */
        Color get_color(void) const noexcept;

        /* Description:
         *  Set new color for checker;
         *
         * Args:
         *  color - new checker's color;
         */
        void set_color(Color color) noexcept;
    };
}

#endif // !CHECKER_HPP