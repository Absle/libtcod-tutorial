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

            // public const references to private variables
            const int &x;
            const int &y;
            const char &symbol;
            const TCODColor &color;
            
            void move(int dx, int dy);

            private:
            int _x, _y;
            char _symbol;
            TCODColor _color;
        };
    }
}

#endif