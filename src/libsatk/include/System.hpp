#ifndef SYSTEM_H
#define SYSTEM_H

#include "Cmp_Move.hpp"
#include "Cmp_Position.hpp"
#include "Cmp_Sprite.hpp"
#include "Entity_Manager.hpp"
#include "Satk_Common.hpp"

#include "libtcod.hpp"

namespace Satk
{
    namespace System
    {
        void move_system(Entity_Manager &emgr, entity_id eid);
        void entity_render_system(Entity_Manager &emgr, entity_id eid, TCODConsole &con);
    }
}

#endif