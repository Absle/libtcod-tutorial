#ifndef COMPONENT_COMMON_H
#define COMPONENT_COMMON_H

#include "Satk_Common.hpp"
#include "Defs.hpp"

namespace Satk
{
    namespace Component
    {
        using add_func = void (*)(entity_id, std::vector<entity_mask>&);
        using remove_func = void (*)(entity_id, std::vector<entity_mask>&);
        using remap_func = void (*)(entity_id, entity_id);
        using stream_func = std::stringstream (*)(entity_id);

        bool register_component(Cmp_Types cmp_num, add_func add, remove_func remove, remap_func remap, stream_func stream);
        void add_component_type(entity_id eid, std::vector<entity_mask> &entities, Cmp_Types cmp_type);
        void remove_component_type(entity_id eid, std::vector<entity_mask> &entities, Cmp_Types cmp_type);
        void remap_component_type(entity_id old_eid, entity_id new_eid, Cmp_Types cmp_type);
        std::stringstream stream_component_type(entity_id eid, Cmp_Types cmp_type);


        // TODO: new stuff
        using add_f = void (*)(entity_id, std::vector<entity_mask>&);
        using add_void_f = void (*)(entity_id, std::vector<entity_mask>&, void*);
        using remove_f = void (*)(entity_id, std::vector<entity_mask>&);
        using remap_f = void (*)(entity_id, entity_id);
        using show_f = std::stringstream (*)(entity_id);

        namespace
        {
            // running count of registered components used to register new ones
            int nreg_comps = 0;
        }

        //const int& nregistered;

        template<class Cmp_T>
        int register_component()
        {
            int reg_id = nreg_comps;
            ++nreg_comps;
            
            // TODO: test?
            std::cout << "Registered " << Cmp_T::name << " at reg_id " << reg_id << '\n';

            return reg_id;
        }

        int get_component_count();
        void add_comp_by_reg(entity_id eid, std::vector<entity_mask> &entities, int reg_id);
    }
}

#endif