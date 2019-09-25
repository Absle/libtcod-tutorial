#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Component_Manager.hpp"
#include "Satk_Common.hpp"

namespace Satk
{
    class Entity_Manager
    {
        private:
        std::vector<entity_mask> entity_vec;
        Component_Manager& cmgr = Component_Manager::get_instance();

        public:
        Entity_Manager() : entity_vec() {}
        
        /* * * * * * * * * * * 
         * Entity Functions  *
         * * * * * * * * * * */

        // add an entity to the manager
        entity_id create();

        // remove an entity from the manager
        void destroy(entity_id eid);

        // get reference to entity vector (USE CAREFULLY)
        std::vector<entity_mask>& entities(){ return entity_vec; }

        /* * * * * * * * * * * *
         * Component Functions *
         * * * * * * * * * * * */

        // add multiple components
        template<class... Cmp_T> void add(entity_id eid);

        // add single component with inital value
        template<class Cmp_T, class... Mems> void add(entity_id eid, std::tuple<Mems...> t);

        // set component value with tuple
        template<class Cmp_T, class... Mems> void set(entity_id eid, Mems... mem);

        // removes Cmp_T component from an entity
        template<class Cmp_T> void remove(entity_id eid);

        // removes all components
        void remove_all(entity_id eid);

        // get ref to eid's component of type Cmp_T
        template<class Cmp_T> Cmp_T& get(entity_id eid);

        /* * * * * * * * * *
         * Debug Functions *
         * * * * * * * * * */

        // get a stream of an entity and its components
        std::stringstream entity_stream(entity_id eid);

        // print a particular entity to clog with a header
        void print_entity(entity_id eid);

        // print all entities to clog with a header
        void print_all_entities();
    };

    template<class... Cmp_T>
    void Entity_Manager::add(entity_id eid)
    {
        (Cmp_T::add_component(eid, entity_vec), ...);
    }

    template<class Cmp_T, class... Mems>
    void Entity_Manager::add(entity_id eid, std::tuple<Mems...> t)
    {
        Cmp_T::add_init_component(eid, entity_vec, t);
    }

    template<class Cmp_T, class... Mems> 
    void Entity_Manager::set(entity_id eid, Mems... mem)
    {
        Cmp_T::set_component(eid, std::make_tuple(mem...));
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