#include "checker.hpp"

namespace game{
    Checker::Checker(const Checker &other){
        this->m_color = other.m_color;
        this->m_current_coord = other.m_current_coord;
    }

    void Checker::make_move_to(const Coord &coord){
        Logger::do_log("Checker::make_move_to (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE);

        Coord distance = m_current_coord - coord;

        // if we want to move checker to the longer distance than it can;
        if (std::abs(distance.coordX) != 1 || std::abs(distance.coordY) != 1){
            std::string error_msg= "Imposible move from (" + std::to_string(m_current_coord.coordX) + "; " +
                std::to_string(m_current_coord.coordY) + ") to (" + std::to_string(coord.coordX) + "; " + std::to_string(coord.coordY) + ").";

            Logger::do_log("Checkers::make_move_to throw WrongCheckerMoveException. Move distance: {" +
                std::to_string(distance.coordX) + "; " + std::to_string(distance.coordY) + "};", Logger::Level::ERROR);
            throw WrongCheckerMoveException(error_msg);
        }

        Logger::do_log("Move (" + Logger::ptr_to_string(this) + ") from {" + std::to_string(m_current_coord.coordX) +
            "; " + std::to_string(m_current_coord.coordY) + "} to {" + std::to_string(coord.coordX) + "; " + 
            std::to_string(coord.coordY) + "}; ", Logger::Level::DEBUG
        );
        m_current_coord = coord;
    }

    bool Checker::operator== (const Checker &other){
        return this->m_color == other.m_color &&
            this->m_current_coord == other.m_current_coord;
    }

    bool Checker::operator!= (const Checker &other){
        return this->m_color != other.m_color ||
            this->m_current_coord != other.m_current_coord;
    }

    Coord Checker::get_current_coord(void) const{
        return m_current_coord;
    }

    void Checker::set_current_coord(const Coord &coord){
        m_current_coord = coord;
    }

    Color Checker::get_color(void) const noexcept{
        return m_color;
    }

    void Checker::set_color(Color color) noexcept{
        m_color = color;
    }
}