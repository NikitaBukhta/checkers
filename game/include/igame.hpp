#ifndef IGAME_HPP
#define IGAME_HPP

namespace game{
    class IGame{
    public:
        virtual int start(void) = 0;
    };
}

#endif // !IGAME_HPP