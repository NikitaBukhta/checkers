#include "player_info.hpp"

namespace game{
    PlayerInfo::PlayerInfo(const std::wstring &nickname){
        Logger::do_log("PlayerInfo constructor called (" + Logger::ptr_to_string(this), Logger::Level::TRACE);

        m_nickname = nickname;
    }

    std::wstring PlayerInfo::get_nickname(void) const{
        Logger::do_log("PlayerInfo::get_nickname (" + Logger::ptr_to_string(this) + "). " +
            "Get returned value is impossible: Type of nickname is wstring instead string",
            Logger::Level::TRACE
        );
        Logger::do_log("PlayerInfo::get_nickname (" + Logger::ptr_to_string(this) + ")" +
            "Log returned value is impossible: Type of nickname is wstring instead string",
            Logger::Level::DEBUG
        );

        return m_nickname;
    }

    void PlayerInfo::get_nickname(std::wstring &nickname) const{
        Logger::do_log("PlayerInfo::get_nickname (" + Logger::ptr_to_string(this) + "). " +
            "Get returned value is impossible: Type of nickname is wstring instead string",
            Logger::Level::TRACE
        );
        Logger::do_log("PlayerInfo::get_nickname (" + Logger::ptr_to_string(this) + ")" +
            "Log returned value is impossible: Type of nickname is wstring instead string",
            Logger::Level::DEBUG
        );

        nickname = m_nickname;
    }

    void PlayerInfo::set_nickname(const std::wstring &nickname){
       Logger::do_log("PlayerInfo::set_nickname (" + Logger::ptr_to_string(this) + "). " +
            "Get returned value is impossible: Type of nickname is wstring instead string",
            Logger::Level::TRACE
        );
        Logger::do_log("PlayerInfo::get_nickname (" + Logger::ptr_to_string(this) + ")" +
            "Log setted value is impossible: Type of nickname is wstring instead string",
            Logger::Level::DEBUG
        );

        m_nickname = nickname;
    }
}