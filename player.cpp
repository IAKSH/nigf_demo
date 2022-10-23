#include "player.hpp"

static void obj_player_move_hook(nigf::Message *msg)
{
    if (msg->get_type() == nigf::MessageType::keyboard_msg)
    {
        auto buffer = static_cast<nigf::KeyboardMessage *>(msg);
        if (buffer->is_key_down())
        {
            switch (buffer->get_code())
            {
            case nigf::KeyboardCode::KEY_W:
                demo::obj_player.set_speed_y(1);
                break;
            case nigf::KeyboardCode::KEY_S:
                demo::obj_player.set_speed_y(-1);
                break;
            case nigf::KeyboardCode::KEY_A:
                demo::obj_player.set_speed_x(-1);
                break;
            case nigf::KeyboardCode::KEY_D:
                demo::obj_player.set_speed_x(-1);
                break;
            default:
                break;
            }
        }
        else
        {
            switch (buffer->get_code())
            {
            case nigf::KeyboardCode::KEY_W:
                demo::obj_player.set_speed_y(0);
                break;
            case nigf::KeyboardCode::KEY_A:
                demo::obj_player.set_speed_y(0);
                break;
            case nigf::KeyboardCode::KEY_S:
                demo::obj_player.set_speed_x(0);
                break;
            case nigf::KeyboardCode::KEY_D:
                demo::obj_player.set_speed_x(0);
                break;
            default:
                break;
            }
        }
    }
}

void demo::initialize()
{
    obj_player.set_position_x(48);
    obj_player.set_position_y(48);
    obj_player.set_size_h(50);
    obj_player.set_size_w(50);

    spr_player.bind_gameobject(obj_player);
    spr_player.add_hook(obj_player_move_hook);
    spr_player.bind_on_tick_func([&](nigf::GameObject &self)
    {
        self.set_position_x(self.get_position_x() - 1);
        self.set_position_y(self.get_position_y() + self.get_speed_y());
    });
}