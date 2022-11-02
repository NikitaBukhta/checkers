#ifndef PLAYER_INFO_HPP
#define PLAYER_INFO_HPP

#include <string>

namespace game{
    class PlayerInfo{
    private:
        std::wstring m_nickname;

    public:
        PlayerInfo(const std::wstring &nickname = L"");

        /* Description:
         *  Return player's nickname;
         */
        std::wstring get_nickname(void) const;

        /* Description:
         *  Return player's nickname;
         *
         * Args:
         *  nickname - container is player's nickname will be written;
         */
        void get_nickname(std::wstring &nickname) const;

        /* Description:
         *  Set new player nickname;
         */
        void set_nickname(const std::wstring &nickname);
    };
}

#endif // !PLAYER_INFO_HPP