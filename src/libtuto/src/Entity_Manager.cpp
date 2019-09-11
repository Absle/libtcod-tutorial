#include "Entity_Manager.hpp"

Satk::entity_id Satk::Entity_Manager::create()
{
    entity_vec.push_back(0);
    return this->entity_vec.size() - 1;
}

void Satk::Entity_Manager::destroy(Satk::entity_id eid)
{
    remove_all(eid); // remove all components from destroyed entity
    
    // swap and pop entity out of vector
    entity_id old_eid = entity_vec.size() - 1;
    std::iter_swap(entity_vec.begin() + eid, entity_vec.end() - 1);
    entity_vec.pop_back();

    for(int i = 0 ; i < Cmp_Types::CMP_END ; ++i)
    {
        Satk::cmp_mask temp_mask = 1 << i;
        if((entity_vec[eid] & temp_mask) == temp_mask)
        {
            Component::remap_component_type(old_eid, eid, Cmp_Types(i));
        }
    }
}

void Satk::Entity_Manager::remove_all(Satk::entity_id eid)
{
    for(int i = 0 ; i < Cmp_Types::CMP_END ; ++i)
    {
        Satk::cmp_mask temp_mask = 1 << i;
        // if ent has cmp with cmp_num of i
        if((entity_vec[eid] & temp_mask) == temp_mask)
        {
            Component::remove_component_type(eid, entity_vec, (Cmp_Types)i);
        }
    }
}