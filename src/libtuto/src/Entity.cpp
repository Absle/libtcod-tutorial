#include "Entity.hpp"

using namespace Satk;
using namespace Satk::Game;

// TODO: put in initializer list
Entity::Entity(int xi, int yi, char symboli, TCODColor colori)
{
    x = xi;
    y = yi;
    symbol = symboli;
    color = colori;
}

void Entity::move(int dx, int dy)
{
    x += dx;
    y += dy;
}