#include "IComponent.hpp"

namespace
{
    void (*removal_function[Satk::CMP_NUM])(Satk::entity_id eid, std::vector<Satk::entity_mask> &entities);
}

void Satk::remove_component_by_type(Satk::entity_id eid, std::vector<Satk::entity_mask> &entities, Satk::Cmp_Types cmp_t)
{
    if(removal_function[cmp_t] != nullptr)
    {
        removal_function[cmp_t](eid, entities);
    }
}