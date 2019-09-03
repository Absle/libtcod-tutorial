#ifndef ICOMPONENT_BASE_H
#define ICOMPONENT_BASE_H

// TODO remove this file?

#include "Defs.hpp"
#include <vector>

namespace Satk
{
    /* * * *
    Purely virtual class intended to be contained in an array and used as a fixed reference to components inheriting IComponent.
    * * * */
    class IComponent_Base
    {
        public:
        virtual void add_component(entity_id eid, std::vector<entity_mask> entities) = 0;
        virtual void remove_component(entity_id eid, std::vector<entity_mask> entities) = 0;
        //virtual void get_component(entity_id eid) = 0;
    };
}

#endif