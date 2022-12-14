#ifndef CHECKER_QUEEN_HPP
#define CHECKER_QUEEN_HPP

#include "checker.hpp"

namespace game{
    class CheckerQueen : public Checker{
    public:
        /* Args:
         *  coord - current checker coord;
         *  color - checker color;
         */
        CheckerQueen(Coord coord = {}, Color color = Color::NO_COLOR) : Checker(coord, color, CheckerType::QUEEN) {};

        CheckerQueen(const CheckerQueen &other) = default;

        CheckerQueen(const Checker &other);

        bool operator== (const CheckerQueen &other) const;

        bool operator!= (const CheckerQueen &other) const;

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
    };
}

#endif // !CHECKER_QUEEN_HPP