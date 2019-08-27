#ifndef ___CMP_NAME____H
#define ___CMP_NAME____H

#include "Defs.hpp"

#include <map>
#include <vector>

namespace Satk
{
    class ___Cmp_Name___
    {
        public:
        ___Cmp_Name(); // constructor

        // component-specific member variables
        
        // static members all components must have
        static std::vector<___CMP_NAME__> vec;
        static std::map<entity_id, cmp_id> map;
        static cmp_mask mask;
    };
}

#endif