#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "Defs.hpp"

#include <map>
#include <vector>

namespace Satk
{
    void register_component(Cmp_Types t, void (*rem_f)(entity_id, std::vector<entity_mask>&));
    void remove_component_by_type(entity_id eid, std::vector<entity_mask> &entities, Cmp_Types cmp_t);

    template<class TCmp, Cmp_Types t ,class... Args>
    class IComponent
    {
        protected:
        IComponent(){}


        public:
        static bool registered;
        static std::vector<TCmp> vec;
        static std::map<entity_id, cmp_id> id_table;
        static cmp_mask mask;

        virtual entity_id owner() =0;

        static void add_component(entity_id eid, std::vector<entity_mask> &entities, Args... args)
        {
            // first time the component is created, register its removal function
            if(!registered)
            {
                registered = true;
                Satk::register_component(t, remove_component);
            }

            // creating and inserting component
            TCmp c = TCmp::_create(eid, args...);
            vec.push_back(c);
            Satk::cmp_id cid = vec.size() - 1;
            id_table.insert(std::map<Satk::entity_id, Satk::cmp_id>::value_type(eid, cid)); // mapping eid to cid
            entities[eid] |= mask;
        }

        static void remove_component(entity_id eid, std::vector<entity_mask> &entities)
        {
            // remove bit from entity mask
            Satk::entity_mask temp_mask = mask;
            temp_mask.flip();
            entities[eid] &= temp_mask;

            // swap and pop_back component object out of vector
            Satk::cmp_id cid = id_table.find(eid)->second;
            std::iter_swap(vec.begin() + cid, vec.end() - 1);
            vec.pop_back();

            id_table[vec[cid].owner()] = cid; // remap entity of former back component to the component's new swapped position
            id_table.erase(eid); // remove mapping of eid
        }

        static TCmp& get_component(entity_id eid)
        {
            return vec[id_table[eid]];
        }
    };
    template<class TCmp, Satk::Cmp_Types t, class... Args>
    bool Satk::IComponent<TCmp, t, Args...>::registered = false;
    
    template<class TCmp, Satk::Cmp_Types t, class... Args>
    std::vector<TCmp> Satk::IComponent<TCmp, t, Args...>::vec;
    
    template<class TCmp, Satk::Cmp_Types t, class... Args>
    std::map<Satk::entity_id, Satk::cmp_id> Satk::IComponent<TCmp, t, Args...>::id_table;
    
    template<class TCmp, Satk::Cmp_Types t, class... Args>
    Satk::cmp_mask Satk::IComponent<TCmp, t, Args...>::mask = 1 << t;
}

#endif