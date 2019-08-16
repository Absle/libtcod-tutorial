#ifndef LIBTUTO_H
#define LIBTUTO_H

#include "libtcod.hpp"

namespace Satk
{
    namespace Input
    {
        enum command_type
        {
            exit,
            fullscreen,
            move,
            nothing
        };
        
        union command_val
        {
            int delta[2];
            bool flag;
        };

        using command = std::tuple<command_type, command_val>;

        command handle_keys(const TCOD_key_t &key);
    }

    namespace Game
    {
        class Entity
        {
            public:
            void move(int dx, int dy);

            private:
            int x, y;
        };
    }
    
}

#endif