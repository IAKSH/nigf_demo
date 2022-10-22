#pragma once
#include <gamespirite.hpp>
#include <msgobject.hpp>

namespace demo
{
    inline auto obj_player = nigf::GameObject(0, 0, "player");
    inline auto spr_player = nigf::GameSpirite(0,"spr_player");
    
    void initialize();
}