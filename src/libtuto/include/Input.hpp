#ifndef INPUT_H
#define INPUT_H

#include "Defs.hpp"

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
}

#endif