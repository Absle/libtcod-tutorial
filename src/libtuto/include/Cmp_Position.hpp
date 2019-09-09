#ifndef CMP_POSITION_H
#define CMP_POSITION_H

/*
COMPONENT ADDING CHECKLIST:
    - Add an element to the Cmp_Types enum
    - Add include of header file to libtuto.hpp
    - Set header guards and class name
    - Create constructor and _create function with proper return type
    - Inherit IComponent with <Cmp_ClassName, CMP_NEW_ENUM> template parameters
    - Add component-specific variables
*/

#include "Defs.hpp"
#include "IComponent.hpp"

#include <map>
#include <vector>

namespace Satk
{
    class Cmp_Position : public IComponent<Cmp_Position, CMP_POSITION>
    {
        private:
        Cmp_Position(entity_id eid) : IComponent(eid), x(0), y(0){}

        public:
        // component-specific member variables
        int x, y;

        // members all components must have
        static Cmp_Position _create(entity_id eid){ return Cmp_Position(eid); }
    };
}

#endif