#include "libtuto.hpp"

using namespace Satk;
using namespace Satk::Input_Manager;

namespace
{
    cmd exit_cmd()
    {
        cmd_val f = {true};
        return std::make_tuple(cmd_type::exit, f);
    }
    
    cmd move_cmd(int dx, int dy)
    {
        cmd_val d = {dx, dy};
        return std::make_tuple(cmd_type::move, d);
    }

    cmd nothing_cmd()
    {
        cmd_val f = {false};
        return std::make_tuple(cmd_type::nothing, f);
    }

    const int up = -1;
    const int down = 1;
    const int left = -1;
    const int right = 1;
}

cmd Input_Manager::handle_keys(const TCOD_key_t &key)
{
    // movement
    if(key.vk == TCODK_UP)
    {
        return move_cmd(0, up);
    }
    else if(key.vk == TCODK_DOWN)
    {
        return move_cmd(0, down);
    }
    else if(key.vk == TCODK_LEFT)
    {
        return move_cmd(left, 0);
    }
    else if(key.vk == TCODK_RIGHT)
    {
        return move_cmd(right, 0);
    }

    // exit the game
    if(key.vk == TCODK_ESCAPE && key.lalt)
    {
        return exit_cmd();
    }

    // no relevant key was pressed
    return nothing_cmd();
}