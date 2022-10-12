#include "ifigure.hpp"

namespace game{
    void Coord::operator= (const Coord &other){
        this->coordX = other.coordX;
        this->coordY = other.coordY;
    }

    bool Coord::operator== (const Coord &other){
        return !(*this != other);
    }

    bool Coord::operator!= (const Coord &other){
        return this->coordX != other.coordX || 
            this->coordY != other.coordY;
    }
}