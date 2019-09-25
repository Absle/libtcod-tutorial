#ifndef CMP_POSITION_H
#define CMP_POSITION_H

/* TODO: fix this checklist, completely borked right now
COMPONENT ADDING CHECKLIST:
    - Add an element to the Cmp_Types enum
    - Add a Cmp_Name
    - Add include of header file to libsatk.hpp
    - Set header guards and class name
    - Add component-specific variables
    - Create constructor and _create function (with proper return type) and accept an owner eid param
    - Inherit IComponent with <Cmp_ClassName, CMP_NEW_ENUM> template parameters
*/

#include "IComponent.hpp"
#include "Satk_Common.hpp"

namespace Satk
{
    class Cmp_Position : public IComponent<Cmp_Position, int, int>
    {
        public:
        // members all components must have
        Cmp_Position(entity_id eid) : IComponent(eid, 0 , 0){}
        Cmp_Position(entity_id eid, int _x, int _y) : IComponent(eid, _x, _y){}

        // component-specific member reference variables
        //int &x, &y; // TODO?
    };

    template<>
    struct Cmp_Type_Traits<Cmp_Position>
    {
        constexpr static char const * name = "Cmp_Position";
    };
}

#endif