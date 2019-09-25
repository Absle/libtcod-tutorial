#include "Input.hpp"

using namespace Satk;

namespace
{
    Input::command exit_command()
    {
        Input::command_val f = {true};
        return std::make_tuple(Input::command_type::exit, f);
    }

    Input::command fullscreen_command()
    {
        Input::command_val f = {true};
        return std::make_tuple(Input::command_type::fullscreen, f);
    }
    
    Input::command move_command(int dx, int dy)
    {
        Input::command_val d = {dx, dy};
        return std::make_tuple(Input::command_type::move, d);
    }

    Input::command nothing_command()
    {
        Input::command_val f = {false};
        return std::make_tuple(Input::command_type::nothing, f);
    }

    const int up = -1;
    const int down = 1;
    const int left = -1;
    const int right = 1;
}

Input::command Input::handle_keys(const TCOD_key_t &key)
{
    // movement
    if(key.vk == TCODK_UP)
    {
        return move_command(0, up);
    }
    else if(key.vk == TCODK_DOWN)
    {
        return move_command(0, down);
    }
    else if(key.vk == TCODK_LEFT)
    {
        return move_command(left, 0);
    }
    else if(key.vk == TCODK_RIGHT)
    {
        return move_command(right, 0);
    }

    // fullscreen
    if(key.vk == TCODK_ENTER && key.lalt)
    {
        return fullscreen_command();
    }

    // exit the game
    if(key.vk == TCODK_ESCAPE && key.lalt)
    {
        return exit_command();
    }

    // no relevant key was pressed
    return nothing_command();
}