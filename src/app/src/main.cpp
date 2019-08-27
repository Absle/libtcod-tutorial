#include "libtcod.hpp"
#include "libtuto.hpp"

using namespace Satk;

int main()
{
    bool running = true;
    int screen_width = 160, screen_height = 100;
    TCOD_key_t key;
    TCOD_mouse_t mouse;
    Game::Entity player(screen_width/2, screen_height/2, '@', TCODColor::white);

    // TODO: test
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
    Cmp_Position::remove_component(p, entities);
    std::cout << p << " : " << entities[p] << std::endl;
    std::cout << Cmp_Position::vec.size() << '\n' << std::endl;

    std::cout << p2 << " : " << entities[p2] << std::endl;
    std::cout << Cmp_Position::vec[Cmp_Position::id_table[p2]].x << ", " << Cmp_Position::vec[Cmp_Position::id_table[p2]].y << '\n' << std::endl;


    TCODConsole::initRoot(screen_width, screen_height, "libtcod C++ tutorial", false);
    TCODConsole con = TCODConsole(screen_width, screen_height);
    con.setDefaultForeground(TCODColor::white);
    con.setDefaultBackground(TCODColor::black);

    // game loop
    while(!TCODConsole::isWindowClosed() && running)
    {
        // constructing console
        con.clear();
        con.putChar(player.x, player.y, '@');
        
        // putting constructed console onto root
        TCODConsole::root->clear();
        TCODConsole::blit(&con, 0, 0, 0, 0, TCODConsole::root, 0, 0);
        TCODConsole::flush();
        
        // translate key input to command
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, &mouse);
        Input::command_type action_type;
        Input::command_val action_val;
        std::tie(action_type, action_val) = Input::handle_keys(key); // breaking data out of tuple

        // move command
        if(action_type == Input::command_type::move)
        {
            int dx = action_val.delta[0];
            int dy = action_val.delta[1];
            player.move(dx, dy);
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
    }

    return 0;
}
