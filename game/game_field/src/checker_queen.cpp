#include "checker_queen.hpp"

namespace game{
    CheckerQueen::CheckerQueen(const Checker &other) : Checker(other){
        std::thread(&Logger::do_log, "CheckerQueen copy constructor called (" + Logger::ptr_to_string(this) + "). Coord = " +
            other.get_current_coord().to_string() + ", color = " + other.color_to_string(), Logger::Level::INFO
        ).detach();

        set_checker_type(CheckerType::QUEEN);
    }

    bool CheckerQueen::operator== (const CheckerQueen &other) const{
        return Checker::operator==(other);
    }

    bool CheckerQueen::operator!= (const CheckerQueen &other) const{
        return Checker::operator!=(other);
    }

    void CheckerQueen::make_move_to(const Coord &coord){
        std::thread(&Logger::do_log, "CheckerQueen::make_move_to (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();

        m_current_coord = coord;
    }
}