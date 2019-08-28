#ifndef CMP_POSITION_H
#define CMP_POSITION_H

#include "Defs.hpp"
#include "IComponent.hpp"

#include <map>
#include <vector>

namespace Satk
{
    class Cmp_Position : public IComponent<Cmp_Position, CMP_POSITION, int, int>
    {
        private:
        Cmp_Position(entity_id eid, int xi, int yi) : owner_id(eid), x(xi), y(yi){}
        entity_id owner_id;

        public:
        // component-specific member variables
        int x, y;

        // members all components must have
        entity_id owner(){return owner_id;}
        static Cmp_Position _create(entity_id eid, int xi, int yi);
    };
}

#endif