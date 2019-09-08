#include "System.hpp"

namespace Satk
{
    namespace System
    {
        void move_system(Entity_Manager &emgr, entity_id eid)
        {
            // return if entity does not have relevant components
            cmp_mask move_mask = Cmp_Position::mask | Cmp_Move::mask;
            if((emgr.entities()[eid] & move_mask) != move_mask) return;

            // add move to position and set move to 0 
            emgr.get<Cmp_Position>(eid).x += emgr.get<Cmp_Move>(eid).dx;
            emgr.get<Cmp_Position>(eid).y += emgr.get<Cmp_Move>(eid).dy;
            emgr.get<Cmp_Move>(eid).dx = 0;
            emgr.get<Cmp_Move>(eid).dy = 0;
        }

        void entity_render_system(Entity_Manager &emgr, entity_id eid, TCODConsole &con)
        {
            // return if entity does not have relevant components
            cmp_mask render_mask = Cmp_Position::mask | Cmp_Sprite::mask;
            if((emgr.entities()[eid] & render_mask) != render_mask) return;

            int x = emgr.get<Cmp_Position>(eid).x;
            int y = emgr.get<Cmp_Position>(eid).y;
            char c = emgr.get<Cmp_Sprite>(eid).ascii;
            TCODColor color = emgr.get<Cmp_Sprite>(eid).color;
            con.putCharEx(x, y, c, color, TCODColor::black); // TODO: handle background colors better
        }
    }
}