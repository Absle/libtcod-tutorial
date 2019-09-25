
#ifndef CMP_SPRITE_H
#define CMP_SPRITE_H

#include "Cmp_Type_Traits.hpp"
#include "IComponent.hpp"
#include "Satk_Common.hpp"

namespace Satk
{
    class Cmp_Sprite : public IComponent<Cmp_Sprite, char, TCODColor, TCODColor>
    {
        public:
        // members all components must have
        Cmp_Sprite(entity_id eid) : IComponent(eid, '?', TCODColor::white, TCODColor::black){}
        Cmp_Sprite(entity_id eid, char _ascii, TCODColor _fore_color, TCODColor _back_color) :
            IComponent(eid, _ascii, _fore_color, _back_color) {}

        // component-specific member variables
        //char ascii;
        //TCODColor color;
        //TCODColor background;
    };

    template<>
    struct Cmp_Type_Traits<Cmp_Sprite>
    {
        constexpr static char const * name = "Cmp_Sprite";
    };
}

#endif
