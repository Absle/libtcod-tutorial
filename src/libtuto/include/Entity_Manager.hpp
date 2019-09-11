#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Component_Common.hpp"
#include "Defs.hpp"
#include <string>
#include <vector>

namespace Satk
{
    class Entity_Manager
    {
        private:
        std::vector<entity_mask> entity_vec;

        public:
        Entity_Manager() : entity_vec() {}
        
        // entity functions
        entity_id create(); // creates entity
        void destroy(entity_id eid); // destroys entity
        std::vector<entity_mask>& entities(){ return entity_vec; }

        // component functions
        template<class Cmp_T> void add(entity_id eid); // adds a Cmp_T component to an entity
        template<class Cmp_T> void remove(entity_id eid); // removes Cmp_T component from an entity
        void remove_all(entity_id eid);
        template<class Cmp_T> Cmp_T& get(entity_id eid);

        // debug functions
        std::stringstream entity_stream(entity_id eid);
        void print_entity(entity_id eid);
        void print_all_entities();
    };

    template<class Cmp_T>
    void Entity_Manager::add(entity_id eid)
    {
        Cmp_T::add_component(eid, entity_vec);
    }

    template<class Cmp_T>
    void Entity_Manager::remove(entity_id eid)
    {
        Cmp_T::remove_component(eid, entity_vec);
    }

    template<class Cmp_T>
    Cmp_T& Entity_Manager::get(entity_id eid)
    {
        return Cmp_T::get_component(eid);
    }
}

#endif