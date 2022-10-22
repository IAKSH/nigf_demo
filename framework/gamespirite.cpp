#include "gamespirite.hpp"

nigf::GameSpirite::GameSpirite(unsigned int id, const char *name)
    : ID(id), NAME(name)
{
}

nigf::GameSpirite::~GameSpirite() {}

void nigf::GameSpirite::on_tick()
{
    if (on_tick_func)
    {
        for (auto &host : hosts)
            on_tick_func(*host);
    }
}

void nigf::GameSpirite::on_hook(nigf::Message &msg)
{
    for (auto &func : hooks)
        func(&msg);
}

void nigf::GameSpirite::bind_on_tick_func(std::function<void(nigf::GameObject &self)> func)
{
    on_tick_func = func;
}

void nigf::GameSpirite::add_hook(std::function<void(nigf::Message *msg)> hook)
{
    hooks.push_back(hook);
}

void nigf::GameSpirite::bind_gameobject(GameObject &go)
{
    std::shared_ptr<GameObject> ptr(&go);
    hosts.push_back(ptr);
}

bool nigf::GameSpirite::check_if_binded()
{
    return !(hosts.size() == 0);
}

const unsigned int nigf::GameSpirite::get_id()
{
    return ID;
}