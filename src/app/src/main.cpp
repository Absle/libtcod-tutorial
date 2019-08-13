#include "libtcod.hpp"
#include "libtuto.hpp"

using namespace Satk;

int main()
{
    bool running = true;
    int screen_width = 80, screen_height = 50;
    int player_x = screen_width / 2, player_y = screen_height / 2;
    TCOD_key_t key;
    TCOD_mouse_t mouse;

    TCODConsole::initRoot(screen_width, screen_height, "libtcod C++ tutorial", false);
    while(!TCODConsole::isWindowClosed() && running)
    {
        TCODConsole::root->clear();
        TCODConsole::root->putChar(player_x, player_y, '@');
        TCODConsole::flush();
        
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, &mouse);
        if(key.vk == TCODK_UP)
        {
            --player_y;
        }
        switch(key.vk)
        {
            case TCODK_UP:
                --player_y;
                break;

            case TCODK_DOWN:
                ++player_y;
                break;

            case TCODK_LEFT:
                --player_x;
                break;

            case TCODK_RIGHT:
                ++player_x;
                break;

            case TCODK_ESCAPE:
                running = false;
                break;

            case TCODK_ALT:
                running = false;
                break;

            default:
                break;
        }
    }

    TCOD_quit();
    return 0;
}
