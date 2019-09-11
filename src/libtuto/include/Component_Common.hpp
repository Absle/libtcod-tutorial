#ifndef COMPONENT_COMMON_H
#define COMPONENT_COMMON_H

#include "Defs.hpp"
#include <array>
#include <cassert>
#include <vector>

namespace Satk
{
    namespace Component
    {
        using add_func = void (*)(entity_id, std::vector<entity_mask>&);
        using remove_func = void (*)(entity_id, std::vector<entity_mask>&);
        using remap_func = void (*)(entity_id, entity_id);

        bool register_component(Cmp_Types cmp_num, add_func add, remove_func remove, remap_func remap);
        void add_component_type(entity_id eid, std::vector<entity_mask> &entities, Cmp_Types cmp_type);
        void remove_component_type(entity_id eid, std::vector<entity_mask> &entities, Cmp_Types cmp_type);
        void remap_component_type(entity_id old_eid, entity_id new_eid, Cmp_Types cmp_type);
    }
}

#endif