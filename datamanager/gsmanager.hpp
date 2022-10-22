#pragma once

#include "objmanager.hpp"

namespace nidm
{
    class GameSpiriteManager : public ObjectManager<nigf::GameSpirite>
    {
    private:
        std::forward_list<nigf::GameSpirite> list;
        unsigned int count = 0;

    public:
        GameSpiriteManager();
        ~GameSpiriteManager();
    };
}