#include "player_info.hpp"

namespace game{
    PlayerInfo::PlayerInfo(const std::wstring &nickname){
        m_nickname = nickname;
    }

    std::wstring PlayerInfo::get_nickname(void) const{
        return m_nickname;
    }

    void PlayerInfo::get_nickname(std::wstring &nickname) const{
        nickname = m_nickname;
    }

    void PlayerInfo::set_nickname(const std::wstring &nickname){
        m_nickname = nickname;
    }
}