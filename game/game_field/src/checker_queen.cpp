#include "checker_queen.hpp"

namespace game{
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