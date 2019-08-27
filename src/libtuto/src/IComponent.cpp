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

/* TODO
template<class TCmp, Satk::Cmp_Types t, class... Args>
bool Satk::IComponent<TCmp, t, Args...>::registered = false;

template<class TCmp, Satk::Cmp_Types t, class... Args>
std::vector<TCmp> Satk::IComponent<TCmp, t, Args...>::vec;

template<class TCmp, Satk::Cmp_Types t, class... Args>
std::map<Satk::entity_id, Satk::cmp_id> Satk::IComponent<TCmp, t, Args...>::id_table;

template<class TCmp, Satk::Cmp_Types t, class... Args>
Satk::cmp_mask Satk::IComponent<TCmp, t, Args...>::mask = 1 << t;

template<class TCmp, Satk::Cmp_Types t, class... Args>
void Satk::IComponent<TCmp, t, Args...>::add_component(Satk::entity_id eid, std::vector<Satk::entity_mask> &entities, Args... args)
{
    // first time the component is created, register it
    if(!registered)
    {
        removal_function[t] = Satk::IComponent<TCmp, t, Args...>::remove_component;
        registered = true;
    }
    TCmp c = TCmp::_create(eid, args...);
    vec.push_back(c);
    Satk::cmp_id cid = vec.size() - 1;
    id_table.insert(std::map<Satk::entity_id, Satk::cmp_id>::value_type(eid, cid));
    entities[eid] |= mask;
}

template<class TCmp, Satk::Cmp_Types t, class... Args>
void Satk::IComponent<TCmp, t, Args...>::remove_component(Satk::entity_id eid, std::vector<Satk::entity_mask> &entities)
{
    // TODO:
    entities[eid] &= !TCmp::mask; // remove bit from entity mask

    // swap and pop_back component object out of vector
    Satk::cmp_id cid = TCmp::id_table.find(eid)->second;
    std::iter_swap(vec.begin() + cid, vec.end() - 1);
    vec.pop_back();
    
    id_table[vec[cid].owner()] = cid; // remap entity of former back component to the component's new swapped position
    id_table.erase(eid); // remove mapping of eid
}
*/