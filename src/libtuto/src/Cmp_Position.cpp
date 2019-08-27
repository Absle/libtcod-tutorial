#include "Cmp_Position.hpp"
#include "libtuto.hpp"

// initialize component-required static members
/* TODO
std::vector<Satk::Cmp_Position> Satk::Cmp_Position::vec;
std::map<Satk::entity_id, Satk::cmp_id> Satk::Cmp_Position::id_table;
Satk::cmp_mask Satk::Cmp_Position::mask = 1 << (Cmp_Types::CMP_POSITION);
*/

Satk::Cmp_Position Satk::Cmp_Position::_create(Satk::entity_id eid, int xi, int yi)
{
    Cmp_Position cmp(eid, xi, yi);
    return cmp;
}