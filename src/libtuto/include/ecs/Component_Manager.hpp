#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "Satk_Common.hpp"

namespace Satk
{
    using add_f = void (*)(entity_id, std::vector<entity_mask>&);
    using add_void_f = void (*)(entity_id, std::vector<entity_mask>&, void*);
    using set_void_f = void (*)(entity_id, void*);
    using remove_f = void (*)(entity_id, std::vector<entity_mask>&);
    using remap_f = void (*)(entity_id, entity_id);
    using show_f = std::stringstream (*)(entity_id);

    class Component_Manager
    {
        private:
        // singleton, private constructor
        Component_Manager(){}
        
        int nreg_comps = 0;
        std::map<std::string, int> name_table;

        std::array<add_f, MAX_NCOMP_TYPES> add_a;
        std::array<add_void_f, MAX_NCOMP_TYPES> add_void_a;
        std::array<set_void_f, MAX_NCOMP_TYPES> set_void_a;
        std::array<remove_f, MAX_NCOMP_TYPES> remove_a;
        std::array<remap_f, MAX_NCOMP_TYPES> remap_a;
        std::array<show_f, MAX_NCOMP_TYPES> show_a;

        public:
        static Component_Manager& get_instance();

        // register new component, called automatically by IComponent
        template<class Cmp_T> int register_component(add_f add, add_void_f add_v, set_void_f set_v, remove_f remove, remap_f remap, show_f show);
        // get the total number of registered components
        int get_component_count();

        #pragma region // trivial wrappers for function pointers...
        // get reg_id mapped to a name
        int get_reg_id(std::string name);
        // add component by reg_id
        void add_comp_by_id(int reg_id, entity_id eid, std::vector<entity_mask>& entities);
        // add and init component by reg_id using void* (BE CAREFUL)
        void add_void_comp_by_id(int reg_id, entity_id eid, std::vector<entity_mask>& entities, void* vals);
        // set component values using void* (BE CAREFUL)
        void set_void_comp_by_id(int reg_id, entity_id eid, void* vals);
        // remove component by reg_id
        void remove_comp_by_id(int reg_id, entity_id eid, std::vector<entity_mask>& entities);
        // remap component to a new eid (usually after destroying an entity) by reg_id
        void remap_comp_by_id(int reg_id, entity_id old_eid, entity_id new_eid);
        // get stringstream of component by reg_id
        std::stringstream show_comp_by_id(int reg_id, entity_id eid);
        #pragma endregion
    };

    template<class Cmp_T>
    int Component_Manager::register_component(add_f add, add_void_f add_v, set_void_f set_v, remove_f remove, remap_f remap, show_f show)
    {
    // make sure MAX_NCOMP_TYPES is not exceeded
    if(nreg_comps >= MAX_NCOMP_TYPES)
    {
        return -1;
    }

    int reg_id = nreg_comps;
    ++nreg_comps;
    add_a[reg_id] = add;
    add_void_a[reg_id] = add_v;
    set_void_a[reg_id] = set_v;
    remove_a[reg_id] = remove;
    remap_a[reg_id] = remap;
    show_a[reg_id] = show;
    std::string name = std::string(Cmp_Type_Traits<Cmp_T>::name);
    name_table.insert(decltype(name_table)::value_type(name, reg_id));
    std::clog << "Registered component \"" << name << "\" at reg_id #" << reg_id << '\n'; // TODO: test?

    return reg_id;
    }
}

#endif