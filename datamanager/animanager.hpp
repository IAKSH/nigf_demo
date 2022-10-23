#pragma once

#include "objmanager.hpp"

namespace nidm
{
    class AnimationManager : public ObjectManager<nigf::Animation>
    {
    public:
        AnimationManager();
        ~AnimationManager();
    };
}