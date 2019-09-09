#ifndef CMP_SPRITE_H
#define CMP_SPRITE_H

#include "Defs.hpp"
#include "IComponent.hpp"

#include "libtcod.hpp"

#include <map>
#include <vector>

namespace Satk
{
    class Cmp_Sprite : public IComponent<Cmp_Sprite, CMP_SPRITE>
    {
        private:
        Cmp_Sprite(entity_id eid) : IComponent(eid), ascii('?'), color(TCODColor::white){}

        public:
        // component-specific member variables
        char ascii;
        TCODColor color;

        // members all components must have
        static Cmp_Sprite _create(entity_id eid){ return Cmp_Sprite(eid); }
    };
}

#endif