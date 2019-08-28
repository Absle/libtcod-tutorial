#include "Cmp_Position.hpp"
#include "libtuto.hpp"

Satk::Cmp_Position Satk::Cmp_Position::_create(Satk::entity_id eid, int xi, int yi)
{
    Cmp_Position cmp(eid, xi, yi);
    return cmp;
}