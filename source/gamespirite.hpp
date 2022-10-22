#pragma once
#include "gameobject.hpp"
#include "msgobject.hpp"
#include <functional>
#include <string>
#include <memory>
#include <vector>

namespace nigf
{
    // GameSpirite is the invisible hand behind GameObject
    // it read infomation from GameObject, and control the GameObject to act.
    // The division between data and logic can reduce function call in each tick, which is benificial to performance.
    // each GameSpirite will be called by tickker
    class GameSpirite
    {
        using api_func = std::function<void(nigf::GameObject &self)>;
        using hook = std::function<void(nigf::Message *msg)>;

    private:
        const unsigned int ID;
        const std::string NAME;
        std::vector<std::shared_ptr<GameObject>> hosts;
        api_func on_tick_func = nullptr;
        std::vector<hook> hooks;

    public:
        GameSpirite(unsigned int id, const char *name);
        ~GameSpirite();

        void on_tick();
        void on_hook(nigf::Message &msg);
        void bind_on_tick_func(api_func func);
        void add_hook(hook func);
        void bind_gameobject(GameObject &go);
        bool check_if_binded();
    };
}