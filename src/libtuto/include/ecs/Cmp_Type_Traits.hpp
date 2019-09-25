#ifndef CMP_TYPE_TRAITS_HPP
#define CMP_TYPE_TRAITS_HPP

//#include "Cmp_Move.hpp"
//#include "Cmp_Position.hpp"
//#include "Cmp_Sprite.hpp"
#include "Satk_Common.hpp"

namespace Satk
{
    template<class T>
    struct Cmp_Type_Traits
    {
        constexpr static char const * name = "UNDEFINED";
    };

    /*
    template<>
    struct Cmp_Type_Traits<Cmp_Move>
    {
        const char* name = "Cmp_Move";
    };

    template<>
    struct Cmp_Type_Traits<Cmp_Position>
    {
        const char* name = "Cmp_Position";
    };

    template<>
    struct Cmp_Type_Traits<Cmp_Sprite>
    {
        const char* name = "Cmp_Sprite";
    };
    */
}



#endif