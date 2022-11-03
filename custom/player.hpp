#pragma once

#include <nigf.hpp>
#include <nidm.hpp>

namespace mydemo::player
{
    void initialize(nidm::AnimationManager &am, nidm::GameObjectManager &gom, nidm::GameSpiriteManager &gsm, nidm::MessageManager &mm,nidm::AudioManager &aum);
    void ontick(nigf::GameObject &self);
    void movment_hook(nigf::Message *msg);
}