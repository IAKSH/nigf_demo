#pragma once

#include "objmanager.hpp"

namespace nidm
{
    class AnimationManager : public ObjectManager<nigf::Animation>
    {
    private:
        std::forward_list<nigf::Animation> list;
        unsigned int count = 0;

    public:
        AnimationManager();
        ~AnimationManager();
    };
}