#include "libtcod.hpp"
#include "libtuto.hpp"

using namespace Satk;

// TODO: need better testing setup
void test();
void entity_manager_test();

int main()
{
    //test(); // TODO: remove/comment/handle somehow

    bool running = true;
    int screen_width = 160, screen_height = 90;
    int map_width = screen_width, map_height = screen_height;

    TCOD_key_t key;
    TCOD_mouse_t mouse;
    Entity_Manager emgr;

    entity_id player = emgr.create();
    emgr.add<Cmp_Position, Cmp_Move, Cmp_Sprite>(player);
    //emgr.add<Cmp_Position>(player);
    emgr.get<Cmp_Position>(player).x = screen_width / 2;
    emgr.get<Cmp_Position>(player).y = screen_height / 2;
    //emgr.add<Cmp_Move>(player);
    //emgr.add<Cmp_Sprite>(player);
    emgr.get<Cmp_Sprite>(player).ascii = '@';

    //TODO: temp, need a better way to generate npc entities
    entity_id npc = emgr.create();
    emgr.add<Cmp_Position>(npc);
    emgr.get<Cmp_Position>(npc).x = screen_width / 2;
    emgr.get<Cmp_Position>(npc).y = screen_height / 2 + 5;
    emgr.add<Cmp_Move>(npc);
    emgr.add<Cmp_Sprite>(npc);
    emgr.get<Cmp_Sprite>(npc).ascii = '@';
    emgr.get<Cmp_Sprite>(npc).color = TCODColor::yellow;
    emgr.get<Cmp_Sprite>(npc).background = TCODColor::black;

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
            System::entity_render_system(emgr, eid, con);
        }
    }

    return 0;
}

// TODO: make proper unit test setup
void test()
{
    std::clog << "Beginning test..." << "\n\n";
    entity_manager_test();
}
// TODO: move to proper unit test setup
void entity_manager_test()
{
    Entity_Manager emgr;
    auto e0 = emgr.create();
    auto e1 = emgr.create();
    auto e2 = emgr.create();
    auto e3 = emgr.create();
    emgr.print_all_entities();

    emgr.add<Cmp_Move>(e0);
    emgr.print_all_entities();
    emgr.add<Cmp_Position>(e1);
    emgr.get<Cmp_Position>(e1).x = 1;
    emgr.print_all_entities();
    emgr.add<Cmp_Sprite>(e2);
    emgr.print_all_entities();
    emgr.add<Cmp_Move>(e3);
    emgr.print_all_entities();
    emgr.add<Cmp_Position>(e3);
    emgr.get<Cmp_Position>(e3).y = 1;
    emgr.print_all_entities();
    emgr.add<Cmp_Sprite>(e3);
    emgr.print_all_entities();
    
    int x1 = emgr.get<Cmp_Position>(e1).x;
    int y1 = emgr.get<Cmp_Position>(e1).y;
    std::clog << "e1 pos: (" << x1 << ", " << y1 << ")" << "\n";
    int x3 = emgr.get<Cmp_Position>(e3).x;
    int y3 = emgr.get<Cmp_Position>(e3).y;
    std::clog << "e3 pos: (" << x3 << ", " << y3 << ")" << "\n";
    emgr.remove<Cmp_Position>(e1);
    emgr.print_all_entities();
    x3 = emgr.get<Cmp_Position>(e3).x;
    y3 = emgr.get<Cmp_Position>(e3).y;
    std::clog << "e3 pos: (" << x3 << ", " << y3 << ")" << "\n";
    emgr.destroy(e1);
    x3 = emgr.get<Cmp_Position>(e3).x;
    y3 = emgr.get<Cmp_Position>(e3).y;
    std::clog << "e3 pos: (" << x3 << ", " << y3 << ")" << "\n";
    emgr.print_all_entities();
}