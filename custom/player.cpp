#include "player.hpp"

#include <audioplayer.hpp>
#include <audio.hpp>

namespace mydemo::player
{
    //nie::AudioPlayer player;

    nidm::AnimationManager *animations;
    nidm::GameObjectManager *gameobjects;
    nidm::GameSpiriteManager *gamespirites;
    nidm::MessageManager *messages;
    nidm::AudioManager *audios;

    nigf::GameObject obj_player(0, 0, "obj_player");
    nigf::GameSpirite spr_player(0, "spr_player");
    // nigf::Animation ani_player(0, "ani_player", 800, {std::make_shared<nigf::Image>("../resource/minami_walk_down_0.jpg"),std::make_shared<nigf::Image>("../resource/minami_walk_down_1.jpg"), std::make_shared<nigf::Image>("../resource/error.jpg")});
        nigf::Animation ani_player(0, "ani_player", 75,{
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

void mydemo::player::initialize(nidm::AnimationManager &am, nidm::GameObjectManager &gom, nidm::GameSpiriteManager &gsm, nidm::MessageManager &mm,nidm::AudioManager &aum)
{
    animations = &am;
    gameobjects = &gom;
    gamespirites = &gsm;
    messages = &mm;
    audios = &aum;

    // Audio Test
    aum.add(nigf::Audio(0,"click","../resource/click.wav"));

    am.add(ani_player);
    obj_player.set_animation(am.get("ani_player"));

    obj_player.set_size_h(125);
    obj_player.set_size_w(150);
    obj_player.set_position_z(0);
    spr_player.bind_on_tick_func(ontick);
    spr_player.add_hook(movment_hook);

    gom.add(obj_player);
    spr_player.bind_gameobject(gom.get(0));
    gsm.add(spr_player);
}

void mydemo::player::ontick(nigf::GameObject &self)
{
    // air wall
    if (self.get_position_y() > 256)
        self.set_position_y(self.get_position_y() - 1);
    if (self.get_position_y() - self.get_size_h() < -256)
        self.set_position_y(self.get_position_y() + 1);
    if (self.get_position_x() < -256)
        self.set_position_x(self.get_position_x() + 1);
    if (self.get_position_x() + self.get_size_w() > 256)
        self.set_position_x(self.get_position_x() - 1);

    self.set_position_x(self.get_position_x() + self.get_speed_x());
    self.set_position_y(self.get_position_y() + self.get_speed_y());
}

void mydemo::player::movment_hook(nigf::Message *msg)
{
    if (msg->get_type() == nigf::MessageType::keyboard_msg)
    {
        auto buffer = static_cast<nigf::KeyboardMessage *>(msg);
        auto &obj = gameobjects->get(0);

        if (buffer->is_key_down())
        {
            switch (buffer->get_code())
            {
            case nigf::KeyboardCode::KEY_W:
                obj.set_speed_y(1);
                break;

            case nigf::KeyboardCode::KEY_A:
                obj.set_speed_x(-1);
                break;

            case nigf::KeyboardCode::KEY_S:
                obj.set_speed_y(-1);
                break;

            case nigf::KeyboardCode::KEY_D:
                obj.set_speed_x(1);
                break;
            /*
            case nigf::KeyboardCode::KEY_0:
                std::cout << "trying to play sound...\n";
                player.play(audios->get("click").get_pcm(),audios->get("click").get_size(),false,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
                break;
            */
            default:
                break;
            }
        }
        else
        {
            switch (buffer->get_code())
            {
            case nigf::KeyboardCode::KEY_W:
                obj.set_speed_y(0);
                break;

            case nigf::KeyboardCode::KEY_A:
                obj.set_speed_x(0);
                break;

            case nigf::KeyboardCode::KEY_S:
                obj.set_speed_y(0);
                break;

            case nigf::KeyboardCode::KEY_D:
                obj.set_speed_x(0);
                break;
            default:
                break;
            }
        }
    }
}