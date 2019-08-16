#ifndef ENTITY_H
#define ENTITY_H

#include "libtcod.hpp"

namespace Satk
{
    namespace Game
    {
        class Entity
        {
            public:
            Entity(int xi, int yi, char symboli, TCODColor colori);
            void move(int dx, int dy);
            int get_x(){return x;};
            int get_y(){return y;};
            char get_symbol(){return symbol;}
            TCODColor get_color(){return color;}

            private:
            int x, y;
            char symbol;
            TCODColor color;
        };
    }
}

#endif