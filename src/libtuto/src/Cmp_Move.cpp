#include "Cmp_Move.hpp"

Satk::Cmp_Move Satk::Cmp_Move::_create(Satk::entity_id eid)
{
    Cmp_Move cmp(eid);
    return cmp;
}