#include "background.hpp"

namespace mydemo::background
{
    nidm::AnimationManager *animations;
    nidm::GameObjectManager *gameobjects;
    nidm::GameSpiriteManager *gamespirites;
    nidm::MessageManager *messages;

    nigf::GameObject obj_background(0, 1, "obj_background");
    nigf::Animation ani_background(1, "ani_background", 200, {std::make_shared<nigf::Image>("../resource/grass_backgroundpng.png")});
}

void mydemo::background::initialize(nidm::AnimationManager &am, nidm::GameObjectManager &gom, nidm::GameSpiriteManager &gsm, nidm::MessageManager &mm)
{
    animations = &am;
    gameobjects = &gom;
    gamespirites = &gsm;
    messages = &mm;

    animations->add(ani_background);

    obj_background.set_size_w(1024);
    obj_background.set_size_h(1024);
    obj_background.set_position_x(-512);
    obj_background.set_position_y(512);
    obj_background.set_position_z(10);
    obj_background.set_animation(animations->get("ani_background"));

    gameobjects->add(obj_background);
}