#ifndef DEFS_H
#define DEFS_H

#include <bitset>

namespace Satk
{
    // entity component system
    enum Cmp_Types
    {
        CMP_MOVE,
        CMP_POSITION,
        CMP_SPRITE,
        CMP_END // the number of component types
    };
    using entity_id = std::size_t;
    using entity_mask = std::bitset<Cmp_Types::CMP_END>;
    using cmp_id = std::size_t;
    using cmp_mask = std::bitset<Cmp_Types::CMP_END>;
}
#endif