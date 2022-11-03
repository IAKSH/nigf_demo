#include "player.hpp"

namespace mydemo::player
{
    nidm::AnimationManager *animations;
    nidm::GameObjectManager *gameobjects;
    nidm::GameSpiriteManager *gamespirites;
    nidm::MessageManager *messages;

    nigf::GameObject obj_player(0, 0, "obj_player");
    nigf::GameSpirite spr_player(0, "spr_player");
    // nigf::Animation ani_player(0, "ani_player", 800, {std::make_shared<nigf::Image>("../resource/minami_walk_down_0.jpg"),std::make_shared<nigf::Image>("../resource/minami_walk_down_1.jpg"), std::make_shared<nigf::Image>("../resource/error.jpg")});
    nigf::Animation ani_player(0, "ani_player", 200, {std::make_shared<nigf::Image>("../resource/minami_walk_down_0.png"), std::make_shared<nigf::Image>("../resource/minami_walk_down_1.png"), std::make_shared<nigf::Image>("../resource/error.png")});
}

void mydemo::player::initialize(nidm::AnimationManager &am, nidm::GameObjectManager &gom, nidm::GameSpiriteManager &gsm, nidm::MessageManager &mm)
{
    animations = &am;
    gameobjects = &gom;
    gamespirites = &gsm;
    messages = &mm;

    am.add(ani_player);
    obj_player.set_animation(am.get("ani_player"));

    // initialize_demo();
    obj_player.set_size_h(200);
    obj_player.set_size_w(200);
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
            }
        }
    }
}