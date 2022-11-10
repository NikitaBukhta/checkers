#ifndef IFIGURE_H
#define IFIGURE_H

namespace game{
    enum class Color : char{
        NO_COLOR = 0,
        WHITE,
        BLACK
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
    };
}

#endif // !IFIGURE_H