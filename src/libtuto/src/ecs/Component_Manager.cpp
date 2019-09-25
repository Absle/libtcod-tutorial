#include "Component_Manager.hpp"

using namespace Satk;

Component_Manager& Component_Manager::get_instance()
{
    static Component_Manager instance;
    return instance;
}

int Component_Manager::get_component_count(){ return nreg_comps; }

int Component_Manager::get_reg_id(std::string name){ return name_table[name]; }

#pragma region // trivial calls to function pointers...
void Component_Manager::add_comp_by_id(int reg_id, entity_id eid, std::vector<entity_mask>& entities)
{
    add_a[reg_id](eid, entities);
}

void Component_Manager::add_void_comp_by_id(int reg_id, entity_id eid, std::vector<entity_mask>& entities, void* vals)
{
    add_void_a[reg_id](eid, entities, vals);
}

void Component_Manager::set_void_comp_by_id(int reg_id, entity_id eid, void* vals)
{
    set_void_a[reg_id](eid, vals);
}

void Component_Manager::remove_comp_by_id(int reg_id, entity_id eid, std::vector<entity_mask>& entities)
{
    remove_a[reg_id](eid, entities);
}

void Component_Manager::remap_comp_by_id(int reg_id, entity_id old_eid, entity_id new_eid)
{
    remap_a[reg_id](old_eid, new_eid);
}

std::stringstream Component_Manager::show_comp_by_id(int reg_id, entity_id eid)
{
    return show_a[reg_id](eid);
}
#pragma endregion