#ifndef DEFS_H
#define DEFS_H

#include <array>
#include <bitset>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Satk
{
    // enum of component types, "type id's" essentially
    enum Cmp_Types
    {
        CMP_MOVE,
        CMP_POSITION,
        CMP_SPRITE,
        CMP_END // the number of component types
    };
    const std::array<std::string, CMP_END> Cmp_Names = 
    {
        "Cmp_Move",
        "Cmp_Position",
        "Cmp_Sprite"
    };
    using entity_id = std::size_t;
    using entity_mask = std::bitset<Cmp_Types::CMP_END>;
    using cmp_id = std::size_t;
    using cmp_mask = std::bitset<Cmp_Types::CMP_END>;
}
#endif