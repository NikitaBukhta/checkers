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

    Coord Coord::operator/ (const int value) const{
        return {static_cast<short>(this->coordX / value), static_cast<short>(this->coordY / value)};
    }

    Coord Coord::operator* (const int value) const{
        return {static_cast<short>(this->coordX * value), static_cast<short>(this->coordY * value)};
    }

    std::string Coord::to_string(void) const{
        std::string ret = '{' + std::to_string(coordX) + "; " + std::to_string(coordY) + '}';
        return ret;
    }
}