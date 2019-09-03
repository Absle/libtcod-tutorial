#include "Entity_Manager.hpp"

Satk::entity_id Satk::Entity_Manager::create()
{
    entity_vec.push_back(0);
    return this->entity_vec.size() - 1;
}

void Satk::Entity_Manager::destroy(Satk::entity_id eid)
{
    
}