#ifndef SATK_COMMON_H
#define SATK_COMMON_H

#include "Cmp_Type_Traits.hpp"

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

// pretty-print a tuple
template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch,Tr>& os, const Tuple& t, std::index_sequence<Is...>)
{
    ((os << (Is == 0? "" : ", ") << std::get<Is>(t)), ...);
}
 
template<class Ch, class Tr, class... Args>
auto& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t)
{
    os << "(";
    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    return os << ")";
}

// pretty-print TCODColor
template<class Ch, class Tr>
auto& operator<<(std::basic_ostream<Ch, Tr>& os, const TCODColor col)
{
    os << (int)col.r << "/" << (int)col.g << "/" << (int)col.b;
    return os;
}

namespace Satk
{
    constexpr int MAX_NCOMP_TYPES = 64;

    using entity_id = std::size_t;
    using entity_mask = std::bitset<MAX_NCOMP_TYPES>;
    using cmp_id = std::size_t;
    using cmp_mask = std::bitset<MAX_NCOMP_TYPES>;
}

#endif