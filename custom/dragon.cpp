#include "dragon.hpp"

namespace mydemo::dragon
{
    nidm::AnimationManager *animations;
    nidm::GameObjectManager *gameobjects;
    nidm::GameSpiriteManager *gamespirites;
    nidm::MessageManager *messages;

    nigf::GameObject obj_dragon(0, 2, "obj_dragon");
    nigf::Animation ani_dragon(2, "ani_dragon", 100,{
        std::make_shared<nigf::Image>("../resource/dragon_1.png"),
        std::make_shared<nigf::Image>("../resource/dragon_2.png"),
        std::make_shared<nigf::Image>("../resource/dragon_3.png"),
        std::make_shared<nigf::Image>("../resource/dragon_4.png"),
        std::make_shared<nigf::Image>("../resource/dragon_5.png"),
        std::make_shared<nigf::Image>("../resource/dragon_6.png"),
    });
}

void mydemo::dragon::initialize(nidm::AnimationManager &am, nidm::GameObjectManager &gom, nidm::GameSpiriteManager &gsm, nidm::MessageManager &mm)
{
    animations = &am;
    gameobjects = &gom;
    gamespirites = &gsm;
    messages = &mm;

    animations->add(ani_dragon);

    obj_dragon.set_size_w(150);
    obj_dragon.set_size_h(150);
    obj_dragon.set_position_x(200);
    obj_dragon.set_position_y(25);
    obj_dragon.set_position_z(15);
    obj_dragon.set_animation(animations->get("ani_dragon"));

    gameobjects->add(obj_dragon);
}