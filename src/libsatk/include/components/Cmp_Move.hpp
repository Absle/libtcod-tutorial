
#ifndef CMP_MOVE_H
#define CMP_MOVE_H

#include "IComponent.hpp"
#include "Satk_Common.hpp"

namespace Satk
{
    class Cmp_Move : public IComponent<Cmp_Move, int, int>
    {
        public:
        // members all components must have
        Cmp_Move(entity_id eid) : IComponent(eid, 0, 0){}
        Cmp_Move(entity_id eid, int _dx, int _dy) : IComponent(eid, _dx, _dy){}

        // component-specific member variables
        //int dx, dy;
    };

    template<>
    struct Cmp_Type_Traits<Cmp_Move>
    {
        constexpr static char const * name = "Cmp_Move";
    };
}

#endif
