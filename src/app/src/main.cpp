#include "libtcod.hpp"
#include "libsatk.hpp"

using namespace Satk;

int main()
{
    bool running = true;
    int screen_width = 160, screen_height = 90;
    int map_width = screen_width, map_height = screen_height;

    TCOD_key_t key;
    TCOD_mouse_t mouse;
    Entity_Manager emgr;

    // make player entity
    entity_id player = emgr.create();
    emgr.add<Cmp_Position, Cmp_Move, Cmp_Sprite>(player);
    emgr.set<Cmp_Position>(player, screen_width / 2, screen_height / 2);
    emgr.set<Cmp_Sprite>(player, '@', TCODColor::white, TCODColor::black);

    //TODO: temp, need a better way to generate npc entities
    entity_id npc = emgr.create();
    emgr.add<Cmp_Position, Cmp_Move, Cmp_Sprite>(npc);
    emgr.set<Cmp_Position>(npc, screen_width / 2, screen_height / 2 - 5);
    emgr.set<Cmp_Sprite>(npc, '@', TCODColor::yellow, TCODColor::black);
    
    emgr.print_all_entities();

    TCODConsole::initRoot(screen_width, screen_height, "libtcod C++ tutorial", false);
    TCODConsole con = TCODConsole(screen_width, screen_height);
    con.setDefaultForeground(TCODColor::white);
    con.setDefaultBackground(TCODColor::black);
    
    /* * * * * * * * * * *
     * Primary Game Loop *
     * * * * * * * * * * */
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
            emgr.set<Cmp_Move>(player, action_val.delta[0], action_val.delta[1]);
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
            System::entity_render_system(emgr, eid, con);
        }
    }

    return 0;
}