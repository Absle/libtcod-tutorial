#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "Component_Manager.hpp"
#include "Satk_Common.hpp"

namespace Satk
{
    template<class Cmp_T, class... Mems>
    class IComponent
    {
        protected:
        IComponent(entity_id eid, Mems... mem) : owner(eid), members(mem...){}
        //static bool registered;
        static int reg_id;
        static std::vector<Cmp_T> vec;
        static std::map<entity_id, cmp_id> id_table;
        entity_id owner;

        public:
        std::tuple<Mems...> members;
        entity_id get_owner(){ return owner; }
        static cmp_mask get_mask() { return 1 << reg_id; }
        static int get_reg_id() { return reg_id; }

        static std::stringstream show(entity_id eid)
        {
            //assert(id_table.find(eid) != id_table.end()); //TODO: fix? need to safely assert somehow
            std::stringstream s;
            s << std::string(Cmp_Type_Traits<Cmp_T>::name) << "[" << eid << ", " << id_table[eid] << "]" << get_component(eid).members;
            return s;
        }

        static void add_component(entity_id eid, std::vector<entity_mask> &entities)
        {
            assert(reg_id >= 0); // ensure component registered; use reg_id variable once
            
            // creating and inserting component
            vec.push_back(Cmp_T(eid));
            cmp_id cid = vec.size() - 1;
            id_table.insert(std::map<entity_id, cmp_id>::value_type(eid, cid)); // mapping eid to cid
            entities[eid] |= get_mask(); // adding mask
        }

        static void add_init_component(entity_id eid, std::vector<entity_mask> &entities, std::tuple<Mems...> vals)
        {
            add_component(eid, entities);
            set_component(eid, vals);
        }

        static void add_void_component(entity_id eid, std::vector<entity_mask> &entities, void* vals)
        {
            add_init_component(eid, entities, *(std::tuple<Mems...>*) vals);
        }

        static void remove_component(entity_id eid, std::vector<entity_mask> &entities)
        {
            // remove bit from entity mask
            entity_mask inverted_mask = get_mask().flip();
            entities[eid] &= inverted_mask;

            // swap and pop_back component object out of vector
            cmp_id cid = id_table.find(eid)->second;
            std::iter_swap((vec.begin() + cid), (vec.end() - 1));
            vec.pop_back();

            id_table[vec[cid].owner] = cid; // remap entity of former back component to the component's new swapped position
            id_table.erase(eid); // remove mapping of eid
        }

        static Cmp_T& get_component(entity_id eid)
        {
            return vec[id_table[eid]];
        }

        static void set_component(entity_id eid, std::tuple<Mems...> vals)
        {
            vec[id_table[eid]].members = vals;
        }

        static void set_void_component(entity_id eid, void* vals)
        {
            set_component(eid, *(std::tuple<Mems...>*) vals);
        }

        // remap component to a new eid (usually after destroying an entity)
        static void remap_component(entity_id old_eid, cmp_id new_eid)
        {
            assert(id_table.find(new_eid) == id_table.end()); // ensure that new_eid is not already in use
            auto table_entry = id_table.find(old_eid);
            assert(table_entry != id_table.end()); // ensure that old_eid is actually in use
            id_table.insert(std::map<entity_id, cmp_id>::value_type(new_eid, table_entry->second)); // inserting value onto new key
            id_table.erase(old_eid);
        }
    };
    
    template<class Cmp_T, class... Mems>
    int IComponent<Cmp_T, Mems...>::reg_id = Component_Manager::get_instance().register_component<Cmp_T>( 
        add_component, 
        add_void_component, 
        set_void_component,
        remove_component,
        remap_component,
        show);

    template<class Cmp_T, class... Mems>
    std::vector<Cmp_T> IComponent<Cmp_T, Mems...>::vec;

    template<class Cmp_T, class... Mems>
    std::map<entity_id, cmp_id> IComponent<Cmp_T, Mems...>::id_table;
}

#endif