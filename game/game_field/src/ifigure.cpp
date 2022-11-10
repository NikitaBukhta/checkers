#include "ifigure.hpp"

namespace game{
    void Coord::operator= (const Coord &other){
        this->coordX = other.coordX;
        this->coordY = other.coordY;
    }

    bool Coord::operator== (const Coord &other) const{
        return !(*this != other);
    }

    bool Coord::operator!= (const Coord &other) const{
        return this->coordX != other.coordX || 
            this->coordY != other.coordY;
    }

    Coord Coord::operator- (const Coord &other) const{
        return {static_cast<short>(this->coordX - other.coordX), static_cast<short>(this->coordY - other.coordY)};
    }

    Coord Coord::operator+ (const Coord &other) const{
        return {static_cast<short>(this->coordX + other.coordX), static_cast<short>(this->coordY + other.coordY)};
    }
}