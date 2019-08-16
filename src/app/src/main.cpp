#include "libtcod.hpp"
#include "libtuto.hpp"

using namespace Satk;

const float transparent_alpha = 0.0f;
const float opaque_alpha = 1.0f;

int main()
{
    bool running = true;
    int screen_width = 80, screen_height = 50;
    int player_x = screen_width / 2, player_y = screen_height / 2;
    
    TCOD_key_t key;
    TCOD_mouse_t mouse;

    TCODConsole::initRoot(screen_width, screen_height, "libtcod C++ tutorial", false);
    //TCODConsole::TCODConsole con(screen_width, screen_height);
    TCODConsole con = TCODConsole(screen_width, screen_height);
    con.setDefaultForeground(TCODColor::white);
    con.setDefaultBackground(TCODColor::black);

    // game loop
    while(!TCODConsole::isWindowClosed() && running)
    {
        
        // constructing console
        con.clear();
        con.putChar(player_x, player_y, '@');
        
        // putting constructed console onto root
        TCODConsole::root->clear();
        TCODConsole::blit(&con, 0, 0, 0, 0, TCODConsole::root, 0, 0);
        //TCODConsole::root->putChar(player_x, player_y, '@');
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
            player_x += dx;
            player_y += dy;
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
