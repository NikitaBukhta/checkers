#ifndef IFIGURE_H
#define IFIGURE_H

#include <string>

namespace game{
    enum class Color : char{
        NO_COLOR = 0,
        WHITE,
        BLACK
    };

    enum class CheckerType : char{
        CHECKER = 0,
        QUEEN = 2
    };

    struct Coord{
        short coordX;
        short coordY;

        void operator= (const Coord &other);

        bool operator== (const Coord &other) const;

        bool operator!= (const Coord &other) const;

        Coord operator- (const Coord &other) const;

        Coord operator+ (const Coord &other) const;

        Coord operator/ (const int value) const; 

        Coord operator* (const int value) const;

        std::string to_string(void) const;
    };

    class IFigure{
    public:
        virtual void make_move_to(const Coord &coord) = 0;

        virtual std::string color_to_string(void) const = 0;

        virtual CheckerType get_checker_type(void) const = 0;
    };
}

#endif // !IFIGURE_H