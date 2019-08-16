#include "Entity.hpp"

using namespace Satk;
using namespace Satk::Game;

Entity::Entity(int xi, int yi, char symboli, TCODColor colori) :
_x(xi), x(_x),
_y(yi), y(_y),
_symbol(symboli), symbol(_symbol),
_color(colori), color(_color)
{

}

void Entity::move(int dx, int dy)
{
    _x += dx;
    _y += dy;
}