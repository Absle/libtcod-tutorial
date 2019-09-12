#ifndef CMP_MOVE_H
#define CMP_MOVE_H

#include "Defs.hpp"
#include "IComponent.hpp"

namespace Satk
{
    class Cmp_Move : public IComponent<Cmp_Move, CMP_MOVE>
    {
        private:
        Cmp_Move(entity_id eid) : IComponent(eid), dx(0), dy(0){}

        public:
        // component-specific member variables
        int dx, dy;

        // members all components must have
        static Cmp_Move _create(entity_id eid){ return Cmp_Move(eid); }
    };
}

#endif