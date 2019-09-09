#include "Component_Common.hpp"

namespace Satk
{
    namespace Component
    {
        namespace
        {
            std::array<add_func, Cmp_Types::CMP_END> add_a = {nullptr};
            std::array<remove_func, Cmp_Types::CMP_END> rem_a;
        }

        bool register_component(Cmp_Types cmp_num, add_func add, remove_func rem)
        {
            assert(add_a[cmp_num] == nullptr && rem_a[cmp_num] == nullptr); // ensure each component is registered exactly once
            add_a[cmp_num] = add;
            rem_a[cmp_num] = rem;
            return true;
        }
    }
}