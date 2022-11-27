#include "checker.hpp"

namespace game{
    Checker::Checker(const Checker &other){
        std::thread(&Logger::do_log, "Checker constructor called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();

        this->m_color = other.m_color;
        this->m_current_coord = other.m_current_coord;
        this->m_checker_type = other.m_checker_type;
    }

    Checker::~Checker(void){
        std::thread(&Logger::do_log, "Checker destructor called (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();
    }

    void Checker::make_move_to(const Coord &coord){
        std::thread(&Logger::do_log,"Checker::make_move_to (" + Logger::ptr_to_string(this) + ")", Logger::Level::INFO).detach();

        Coord distance = m_current_coord - coord;

        // if we want to move checker to the longer distance than it can;
        if (std::abs(distance.coordX) != 1 || std::abs(distance.coordY) != 1){
            std::string error_msg= "Imposible move from " + m_current_coord.to_string()  + " to " + coord.to_string() + 
                ". Distance: " + distance.to_string();

            std::thread(&Logger::do_log, "Checkers::make_move_to (" + Logger::ptr_to_string(this) + ") throw WrongCheckerMoveException. " +
                error_msg, Logger::Level::ERROR
            ).detach();

            throw WrongCheckerMoveException(error_msg);
        }

        std::thread(&Logger::do_log, "Move (" + Logger::ptr_to_string(this) + ") from " + m_current_coord.to_string() + " to " + coord.to_string(), Logger::Level::DEBUG).detach();

        m_current_coord = coord;
    }

    bool Checker::operator== (const Checker &other) const{
        return this->m_color == other.m_color &&
            this->m_current_coord == other.m_current_coord;
    }

    bool Checker::operator!= (const Checker &other) const{
        return this->m_color != other.m_color ||
            this->m_current_coord != other.m_current_coord;
    }

    Coord Checker::get_current_coord(void) const{
        std::thread(&Logger::do_log, "Checker::get_current_coord called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE).detach();
        
        return m_current_coord;
    }

    void Checker::set_current_coord(const Coord &coord){
        std::thread(&Logger::do_log, "Checker::set_current_coord called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE).detach();

        m_current_coord = coord;
    }

    Color Checker::get_color(void) const noexcept{
        std::thread(&Logger::do_log, "Checker::get_color called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE).detach();

        return m_color;
    }

    void Checker::set_color(Color color) noexcept{
        std::thread(&Logger::do_log, "Checker::set_color called (" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE).detach();

        m_color = color;
    }

    std::string Checker::color_to_string() const{
        std::thread(&Logger::do_log, "Checker::color_to_string called )" + Logger::ptr_to_string(this) + ")", Logger::Level::TRACE).detach();

        switch(m_color){
            case Color::BLACK:
                return "black";

            case Color::WHITE:
                return "white";

            default:
                return "no color";
        }
    }

    CheckerType Checker::get_checker_type(void) const{
        std::thread(&Logger::do_log, "Checker::get_checker_type called (" + Logger::ptr_to_string(this), Logger::Level::TRACE).detach();

        return m_checker_type;
    }

    Coord Checker::get_max_distance_to_move(void){
        std::thread(&Logger::do_log, "Checker::get_max_distance_to_move called (static)", Logger::Level::TRACE).detach();

        return {1, 1};
    }
}