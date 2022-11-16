#ifndef IFIGURE_H
#define IFIGURE_H

#include <string>

namespace game{
    enum class Color : char{
        NO_COLOR = 0,
        WHITE,
        BLACK,
        WHITE_QUEEN,
        BLACK_QUEEN
    };

    struct Coord{
        short coordX;
        short coordY;

        void operator= (const Coord &other);

        bool operator== (const Coord &other) const;

        bool operator!= (const Coord &other) const;

        Coord operator- (const Coord &other) const;

        Coord operator+ (const Coord &other) const;
    };

    class IFigure{
    public:
        virtual void make_move_to(const Coord &coord) = 0;

        virtual std::string color_to_string(void) const = 0;
    };
}

#endif // !IFIGURE_H