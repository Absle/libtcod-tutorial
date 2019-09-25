#include "Entity_Manager.hpp"

Satk::entity_id Satk::Entity_Manager::create()
{
    entity_vec.push_back(0);
    return this->entity_vec.size() - 1;
}

void Satk::Entity_Manager::destroy(Satk::entity_id eid)
{
    assert(eid < entity_vec.size());
    remove_all(eid); // remove all components from destroyed entity
    
    // swap and pop entity out of vector
    entity_id old_eid = entity_vec.size() - 1;
    std::iter_swap(entity_vec.begin() + eid, entity_vec.end() - 1);
    entity_vec.pop_back();

    for(int i = 0 ; i < cmgr.get_component_count() ; ++i)
    {
        Satk::cmp_mask temp_mask = 1 << i;
        if((entity_vec[eid] & temp_mask) == temp_mask)
        {
            cmgr.remap_comp_by_id(i, old_eid, eid);
        }
    }
}

void Satk::Entity_Manager::remove_all(Satk::entity_id eid)
{
    for(int i = 0 ; i < cmgr.get_component_count() ; ++i)
    {
        Satk::cmp_mask temp_mask = 1 << i;
        // if ent has cmp with cmp_num of i
        if((entity_vec[eid] & temp_mask) == temp_mask)
        {
            cmgr.remove_comp_by_id(i, eid, entity_vec);
        }
    }
}

// debug functions
namespace
{
    void print_entity_header()
    {
        std::clog << "\t\t" << "MASK" << "\t\t" << "COMP LIST" << "\n";
        std::clog << "=================================================" << "\n";
    }
}

std::stringstream Satk::Entity_Manager::entity_stream(entity_id eid)
{
    assert(eid < entity_vec.size());
    std::stringstream s;
    std::string bitstr = entity_vec[eid].to_string('-').substr(MAX_NCOMP_TYPES - cmgr.get_component_count());
    s << "Entity #" << eid << ":\t" << bitstr << "\t\t";
    for(int i = 0 ; i < cmgr.get_component_count() ; ++i)
    {
        cmp_mask temp = 1 << i;
        if((entity_vec[eid] & temp) == temp)
        {
            s << cmgr.show_comp_by_id(i, eid).rdbuf() << " ; ";
        }
    }
    s << "\n";
    return s;
}

void Satk::Entity_Manager::print_entity(entity_id eid)
{
    print_entity_header();
    std::clog << entity_stream(eid).rdbuf() << std::endl;
}

void Satk::Entity_Manager::print_all_entities()
{
    print_entity_header();
    for(int i = 0 ; i < entity_vec.size() ; ++i)
    {
        std::clog << entity_stream(i).rdbuf();
    }
    std::clog << std::endl;
}