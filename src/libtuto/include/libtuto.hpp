#ifndef LIBTUTO_H
#define LIBTUTO_H

#include "Cmp_Move.hpp"
#include "Cmp_Position.hpp"
#include "Cmp_Sprite.hpp"
#include "Defs.hpp"
#include "Entity_Manager.hpp"
#include "Entity.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include "System.hpp"

#include "libtcod.hpp"

namespace Satk
{
    namespace Input{} // implemented externally

    namespace Game
    {
        class Entity;
    }

    //TODO: remove
    //class Cmp_Move;
    //class Cmp_Position;
    //class Cmp_Sprite;
}

#endif