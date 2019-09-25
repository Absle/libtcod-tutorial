#include "System.hpp"

namespace Satk
{
    namespace System
    {
        void move_system(Entity_Manager &emgr, entity_id eid)
        {
            // return if entity does not have relevant components
            cmp_mask move_mask = Cmp_Position::get_mask() | Cmp_Move::get_mask();
            if((emgr.entities()[eid] & move_mask) != move_mask) return;

            // add move to position and set move to 0
            const int X = 0, Y = 1;
            auto& move = emgr.get<Cmp_Move>(eid).members;
            auto& pos = emgr.get<Cmp_Position>(eid).members;
            int dx = std::get<X>(move);
            int dy = std::get<Y>(move);
            int x = std::get<X>(pos);
            int y = std::get<Y>(pos);
            emgr.set<Cmp_Position>(eid, x + dx, y + dy);
            emgr.set<Cmp_Move>(eid, 0, 0);
        }

        void entity_render_system(Entity_Manager &emgr, entity_id eid, TCODConsole &con)
        {
            // return if entity does not have relevant components
            cmp_mask render_mask = Cmp_Position::get_mask() | Cmp_Sprite::get_mask();
            if((emgr.entities()[eid] & render_mask) != render_mask) return;

            // render entity to con
            const int X = 0, Y = 1, ASCII = 0, FORE_COLOR = 1, BACK_COLOR = 2;
            auto& pos = emgr.get<Cmp_Position>(eid).members;
            auto& sprite = emgr.get<Cmp_Sprite>(eid).members;
            int x = std::get<X>(pos);
            int y = std::get<Y>(pos);
            char c = std::get<ASCII>(sprite);
            auto foreground = std::get<FORE_COLOR>(sprite);
            auto background = std::get<BACK_COLOR>(sprite);
            con.putCharEx(x, y, c, foreground, background);
        }
    }
}