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

        bool register_component(Cmp_Types cmp_num, add_func add, remove_func rem);
    }
}

#endif