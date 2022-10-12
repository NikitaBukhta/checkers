#ifndef IFIGURE_H
#define IFIGURE_H

namespace game{
    enum class Color : char{
        no_color = 0,
        white,
        black
    };

    struct Coord{
        short coordX;
        short coordY;

        void operator= (const Coord &other);

        bool operator== (const Coord &other);

        bool operator!= (const Coord &other);
    };

    class IFigure{
    public:
        virtual void make_move_to(const Coord &coord) = 0;
    };
}

#endif // !IFIGURE_H