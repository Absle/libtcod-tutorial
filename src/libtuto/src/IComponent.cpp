#include "IComponent.hpp"

namespace
{
    void (*removal_function[Satk::CMP_NUM])(Satk::entity_id eid, std::vector<Satk::entity_mask> &entities);
}

void Satk::register_component(Satk::Cmp_Types t, void (*rem_f)(Satk::entity_id, std::vector<Satk::entity_mask>&))
{
    removal_function[t] = rem_f;
}

void Satk::remove_component_by_type(Satk::entity_id eid, std::vector<Satk::entity_mask> &entities, Satk::Cmp_Types cmp_t)
{
    if(removal_function[cmp_t] != nullptr)
    {
        removal_function[cmp_t](eid, entities);
    }
}

