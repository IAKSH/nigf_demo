#pragma once

#include "objmanager.hpp"

namespace nidm
{
    class GameObjectManager : public ObjectManager<nigf::GameObject>
    {
    private:
        std::forward_list<nigf::GameObject> list;
        unsigned int count = 0;

    public:
        GameObjectManager();
        ~GameObjectManager();

        void add(nigf::GameObject go)
        {
            go.reset_id(count++);
            list.push_front(go);
        }
    };
}