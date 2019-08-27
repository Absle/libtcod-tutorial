#ifndef DEFS_H
#define DEFS_H

#include <bitset>

namespace Satk
{
    // entity component system
    enum Cmp_Types
    {
        CMP_POSITION,
        CMP_MOVE,
        CMP_NUM // the number of component types
    };
    using entity_id = std::size_t;
    using entity_mask = std::bitset<Cmp_Types::CMP_NUM>;
    using cmp_id = std::size_t;
    using cmp_mask = std::bitset<Cmp_Types::CMP_NUM>;
}
#endif