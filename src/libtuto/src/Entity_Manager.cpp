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

// debug functions
namespace
{
    void print_entity_header()
    {
        std::clog << "\t\t" << "MASK" << "\t" << "CMP_NAME LIST" << "\n";
        std::clog << "=========================================" << "\n";
    }
}

std::stringstream Satk::Entity_Manager::entity_stream(entity_id eid)
{
    assert(eid < entity_vec.size());
    std::stringstream s;
    s << "Entity #" << eid << ":\t" << entity_vec[eid] << "\t";
    for(int i = 0 ; i < Cmp_Types::CMP_END ; ++i)
    {
        cmp_mask temp = 1 << i;
        if((entity_vec[eid] & temp) == temp)
        {
            s << Cmp_Names[i] << "(" << Component::stream_component_type(eid, Cmp_Types(i)).rdbuf() << ")" << ", ";
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