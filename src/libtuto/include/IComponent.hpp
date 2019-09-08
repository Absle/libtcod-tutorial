#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "Defs.hpp"
#include <map>
#include <memory>
#include <vector>

namespace Satk
{
    template<class Cmp_T, Cmp_Types t>
    class IComponent
    {
        protected:
        IComponent(entity_id eid) : owner_id(eid){}
        //static bool registered; // TODO: remove/fix
        static std::vector<Cmp_T> vec;
        static std::map<entity_id, cmp_id> id_table;
        entity_id owner_id;

        public:
        entity_id owner(){ return owner_id; }
        const static cmp_mask mask;
        //static cmp_mask mask(){ return mask; }

        static void add_component(entity_id eid, std::vector<entity_mask> &entities)
        {
            // first time the component is created, register its removal function
            /* TODO: remove/fix registration process
            if(!registered)
            {
                registered = true;
                Satk::register_component(t, remove_component);
            }
            */

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
            entity_mask temp_mask = mask;
            temp_mask.flip();
            entities[eid] &= temp_mask;

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
    };
    // TODO: remove/fix
    //template<class Cmp_T, Cmp_Types t>
    //bool IComponent<Cmp_T, t>::registered = false;
    
    template<class Cmp_T, Cmp_Types t>
    std::vector<Cmp_T> IComponent<Cmp_T, t>::vec;
    
    template<class Cmp_T, Cmp_Types t>
    std::map<entity_id, cmp_id> IComponent<Cmp_T, t>::id_table;
    
    template<class Cmp_T, Cmp_Types t>
    const cmp_mask IComponent<Cmp_T, t>::mask = 1 << t;
}

#endif