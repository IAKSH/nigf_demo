#include "sunflower.hpp"

namespace mydemo::sunflower
{
    nidm::AnimationManager *animations;
    nidm::GameObjectManager *gameobjects;
    nidm::GameSpiriteManager *gamespirites;
    nidm::MessageManager *messages;
    nidm::AudioManager *audios;

    nigf::GameObject obj_sunflower(0, 2, "obj_sunflower");
    nigf::Animation ani_sunflower(2, "ani_sunflower", 75,{
        std::make_shared<nigf::Image>("../resource/1.png"),
        std::make_shared<nigf::Image>("../resource/2.png"),
        std::make_shared<nigf::Image>("../resource/3.png"),
        std::make_shared<nigf::Image>("../resource/4.png"),
        std::make_shared<nigf::Image>("../resource/5.png"),
        std::make_shared<nigf::Image>("../resource/6.png"),
        std::make_shared<nigf::Image>("../resource/7.png"),
        std::make_shared<nigf::Image>("../resource/8.png"),
        std::make_shared<nigf::Image>("../resource/9.png"),
        std::make_shared<nigf::Image>("../resource/10.png"),
        std::make_shared<nigf::Image>("../resource/11.png"),
        std::make_shared<nigf::Image>("../resource/12.png"),
        std::make_shared<nigf::Image>("../resource/13.png"),
        std::make_shared<nigf::Image>("../resource/14.png"),
        std::make_shared<nigf::Image>("../resource/15.png"),
        std::make_shared<nigf::Image>("../resource/16.png"),
        std::make_shared<nigf::Image>("../resource/17.png"),
        std::make_shared<nigf::Image>("../resource/18.png")
    });
}

void mydemo::sunflower::initialize(nidm::AnimationManager &am, nidm::GameObjectManager &gom, nidm::GameSpiriteManager &gsm, nidm::MessageManager &mm,nidm::AudioManager &aum)
{
    animations = &am;
    gameobjects = &gom;
    gamespirites = &gsm;
    messages = &mm;
    audios = &aum;

    animations->add(ani_sunflower);

    obj_sunflower.set_size_w(150);
    obj_sunflower.set_size_h(125);
    obj_sunflower.set_position_x(0);
    obj_sunflower.set_position_y(0);
    obj_sunflower.set_position_z(15);
    obj_sunflower.set_animation(animations->get("ani_sunflower"));

    gameobjects->add(obj_sunflower);
}