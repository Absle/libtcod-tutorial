#include "libtcod.hpp"
#include "libtuto.hpp"

using namespace Satk;

int main()
{
    bool running = true;
    int screen_width = 160, screen_height = 90;
    TCOD_key_t key;
    TCOD_mouse_t mouse;
    Entity_Manager emgr;

    entity_id player = emgr.create();
    emgr.add<Cmp_Position>(player);
    emgr.get<Cmp_Position>(player).x = screen_width / 2;
    emgr.get<Cmp_Position>(player).y = screen_height / 2;
    emgr.add<Cmp_Move>(player);
    emgr.add<Cmp_Sprite>(player);
    emgr.get<Cmp_Sprite>(player).ascii = '@';
    emgr.get<Cmp_Sprite>(player).color = TCODColor::white;

    TCODConsole::initRoot(screen_width, screen_height, "libtcod C++ tutorial", false);
    TCODConsole con = TCODConsole(screen_width, screen_height);
    con.setDefaultForeground(TCODColor::white);
    con.setDefaultBackground(TCODColor::black);

    // primary game loop
    while(!TCODConsole::isWindowClosed() && running)
    {   
        // blitting console rendered last loop onto root
        TCODConsole::root->clear();
        TCODConsole::blit(&con, 0, 0, 0, 0, TCODConsole::root, 0, 0);
        TCODConsole::flush();
        
        /* * * * * * * * * *
         * Input Handling  *
         * * * * * * * * * */
        // translate key input to command
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, &mouse);
        Input::command_type action_type;
        Input::command_val action_val;
        std::tie(action_type, action_val) = Input::handle_keys(key); // breaking data out of tuple

        // move command
        if(action_type == Input::command_type::move)
        {
            emgr.get<Cmp_Move>(player).dx = action_val.delta[0];
            emgr.get<Cmp_Move>(player).dy = action_val.delta[1];
        }

        // fullscreen command
        if(action_type == Input::command_type::fullscreen)
        {
            TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
        }

        // exit command
        if(action_type == Input::command_type::exit && action_val.flag)
        {
            TCOD_quit();
            running = false;
        }

        /* * * * * * * * * * * * * * *
         * Apply systems to entities *
         * * * * * * * * * * * * * * */
        con.clear();
        for(int eid = 0 ; eid < emgr.entities().size() ; ++eid)
        {
            System::move_system(emgr, eid);
            System::render_system(emgr, eid, con);
        }
    }

    return 0;
}
