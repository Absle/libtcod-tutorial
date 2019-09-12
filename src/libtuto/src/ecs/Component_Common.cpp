#include "Component_Common.hpp"

namespace Satk
{
    namespace Component
    {
        namespace
        {
            std::array<add_func, Cmp_Types::CMP_END> add_a;
            std::array<remove_func, Cmp_Types::CMP_END> remove_a;
            std::array<remap_func, Cmp_Types::CMP_END> remap_a;
            std::array<stream_func, Cmp_Types::CMP_END> stream_a;
        }

        bool register_component(Cmp_Types cmp_num, add_func add, remove_func remove, remap_func remap, stream_func stream)
        {
            // ensure each component is registered exactly once
            assert( add_a[cmp_num] == nullptr && 
                    remove_a[cmp_num] == nullptr && 
                    remap_a[cmp_num] == nullptr && 
                    stream_a[cmp_num] == nullptr);
            add_a[cmp_num] = add;
            remove_a[cmp_num] = remove;
            remap_a[cmp_num] = remap;
            stream_a[cmp_num] = stream;
            return true;
        }

        void add_component_type(entity_id eid, std::vector<entity_mask> &entities, Cmp_Types cmp_type)
        {
            add_a[cmp_type](eid, entities);
        }

        void remove_component_type(entity_id eid, std::vector<entity_mask> &entities, Cmp_Types cmp_type)
        {
            remove_a[cmp_type](eid, entities);
        }

        void remap_component_type(entity_id old_eid, entity_id new_eid, Cmp_Types cmp_type)
        {
            remap_a[cmp_type](old_eid, new_eid);
        }

        std::stringstream stream_component_type(entity_id eid, Cmp_Types cmp_type)
        {
            return stream_a[cmp_type](eid);
        }
    }
}