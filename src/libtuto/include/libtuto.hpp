#ifndef LIBTUTO_H
#define LIBTUTO_H

#include "libtcod.hpp"

namespace Satk
{
    namespace Input_Manager
    {
        enum cmd_type
        {
            exit,
            move,
            nothing
        };
        
        union cmd_val
        {
            int delta[2];
            bool flag;
        };

        using cmd = std::tuple<cmd_type, cmd_val>;

        cmd handle_keys(const TCOD_key_t &key);
    }

    class Entity
    {
    public:
        void move(int dx, int dy);

    private:
        int x, y;
    };
}

#endif