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
    
    // entities.push_back(0);
    // entity_id player = entities.size() - 1;
    // Cmp_Position::add_component(player, entities, screen_width/2, screen_height/2);
    // Cmp_Move::add_component(player, entities, 0, 0);
    // Cmp_Sprite::add_component(player, entities, '@', TCODColor::white);

    //Game::Entity player(screen_width/2, screen_height/2, '@', TCODColor::white); // TODO: remove

    // TODO: test
    /*
    std::vector<Satk::entity_mask> entities;
    entities.push_back(0);
    entity_id p = entities.size() - 1;
    std::cout << p << " : " << entities[p] << std::endl;
    Cmp_Position::add_component(p, entities, 1, 1);
    std::cout << p << " : " << entities[p] << std::endl;
    std::cout << Cmp_Position::vec[Cmp_Position::id_table[p]].x << ", " << Cmp_Position::vec[Cmp_Position::id_table[p]].y << '\n' << std::endl;

    entities.push_back(0);
    entity_id p2 = entities.size() - 1;
    std::cout << p2 << " : " << entities[p2] << std::endl;
    Cmp_Position::add_component(p2, entities, 2, 2);
    std::cout << p2 << " : " << entities[p2] << std::endl;
    std::cout << Cmp_Position::vec[Cmp_Position::id_table[p2]].x << ", " << Cmp_Position::vec[Cmp_Position::id_table[p2]].y << '\n' << std::endl;

    std::cout << p << " : " << entities[p] << std::endl;
    std::cout << Cmp_Position::vec.size() << std::endl;
    //Cmp_Position::remove_component(p, entities);
    Satk::remove_component_by_type(p, entities, Cmp_Types::CMP_POSITION);
    std::cout << p << " : " << entities[p] << std::endl;
    std::cout << Cmp_Position::vec.size() << '\n' << std::endl;

    std::cout << p2 << " : " << entities[p2] << std::endl;
    std::cout << Cmp_Position::vec[Cmp_Position::id_table[p2]].x << ", " << Cmp_Position::vec[Cmp_Position::id_table[p2]].y << '\n' << std::endl;
    Cmp_Position::get_component(p2).x += 1;
    Cmp_Position::get_component(p2).y += 1;
    std::cout << Cmp_Position::vec[Cmp_Position::id_table[p2]].x << ", " << Cmp_Position::vec[Cmp_Position::id_table[p2]].y << '\n' << std::endl;
    */

    TCODConsole::initRoot(screen_width, screen_height, "libtcod C++ tutorial", false);
    TCODConsole con = TCODConsole(screen_width, screen_height);
    con.setDefaultForeground(TCODColor::white);
    con.setDefaultBackground(TCODColor::black);

    // primary game loop
    while(!TCODConsole::isWindowClosed() && running)
    {
        // // constructing console
        // con.clear();
        // //TODO: proper rendering and entity loop (probably here?)
        // con.putChar(Cmp_Position::get_component(player).x, Cmp_Position::get_component(player).y, Cmp_Sprite::get_component(player).ascii);
        
        // blitting constructed console onto root
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
