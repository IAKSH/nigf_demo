#pragma once

#include "objmanager.hpp"

namespace nidm
{
    class GameObjectManager : public ObjectManager<nigf::GameObject>
    {
    public:
        GameObjectManager();
        ~GameObjectManager();

        void add(nigf::GameObject go)
        {
            go.reset_id(count);
            list.push_front(go);
        }
    };
}