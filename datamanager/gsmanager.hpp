#pragma once

#include "objmanager.hpp"

namespace nidm
{
    class GameSpiriteManager : public ObjectManager<nigf::GameSpirite>
    {
    public:
        GameSpiriteManager();
        ~GameSpiriteManager();
    };
}