#ifndef DEFS_H
#define DEFS_H

#include "libtcod.hpp"

#include <array>
#include <bitset>
#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
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
}
#endif