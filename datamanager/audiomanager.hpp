#pragma once

#include "objmanager.hpp"
#include <audio.hpp>

namespace nidm
{
    class AudioManager : public nidm::ObjectManager<nigf::Audio>
    {
    public:
        AudioManager();
        ~AudioManager();
    };
}