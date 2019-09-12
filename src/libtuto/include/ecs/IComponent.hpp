#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "Defs.hpp"
#include "Component_Common.hpp"

namespace Satk
{
    template<class Cmp_T, Cmp_Types cmp_num>
    class IComponent
    {
        protected:
        IComponent(entity_id eid) : owner_id(eid){}
        static bool registered;
        static std::vector<Cmp_T> vec;
        static std::map<entity_id, cmp_id> id_table;
        entity_id owner_id;

        public:
        const static cmp_mask mask;
        entity_id owner(){ return owner_id; }
        // TODO: expand this? problems using non-static function (ie virtual)
        static std::stringstream component_stream(entity_id eid)
        {
            std::stringstream s;
            s << "[" << id_table[eid] << "]";
            return s;
        }

        static void add_component(entity_id eid, std::vector<entity_mask> &entities)
        {
            assert(registered); // ensure component registered; use registered variable once
            
            // creating and inserting component
            Cmp_T c = Cmp_T::_create(eid);
            vec.push_back(c);
            cmp_id cid = vec.size() - 1;
            id_table.insert(std::map<entity_id, cmp_id>::value_type(eid, cid)); // mapping eid to cid
            entities[eid] |= mask;
        }

        static void remove_component(entity_id eid, std::vector<entity_mask> &entities)
        {
            // remove bit from entity mask
            entity_mask inverted_mask = mask;
            inverted_mask.flip();
            entities[eid] &= inverted_mask;

            // swap and pop_back component object out of vector
            cmp_id cid = id_table.find(eid)->second;
            std::iter_swap(vec.begin() + cid, vec.end() - 1);
            vec.pop_back();

            id_table[vec[cid].owner_id] = cid; // remap entity of former back component to the component's new swapped position
            id_table.erase(eid); // remove mapping of eid
        }

        static Cmp_T& get_component(entity_id eid)
        {
            return vec[id_table[eid]];
        }

        static void remap_component(entity_id old_eid, cmp_id new_eid)
        {
            assert(id_table.find(new_eid) == id_table.end()); // ensure that new_eid is not already in use
            auto table_entry = id_table.find(old_eid);
            assert(table_entry != id_table.end()); // ensure that old_eid is actually in use
            id_table.insert(std::map<entity_id, cmp_id>::value_type(new_eid, table_entry->second)); // inserting value onto new key
            id_table.erase(old_eid);
        }
    };
    
    template<class Cmp_T, Cmp_Types cmp_num>
    bool IComponent<Cmp_T, cmp_num>::registered = Component::register_component(cmp_num, add_component, remove_component, remap_component, component_stream);
    
    template<class Cmp_T, Cmp_Types cmp_num>
    std::vector<Cmp_T> IComponent<Cmp_T, cmp_num>::vec;
    
    template<class Cmp_T, Cmp_Types cmp_num>
    std::map<entity_id, cmp_id> IComponent<Cmp_T, cmp_num>::id_table;
    
    template<class Cmp_T, Cmp_Types cmp_num>
    const cmp_mask IComponent<Cmp_T, cmp_num>::mask = 1 << cmp_num;
}

#endif