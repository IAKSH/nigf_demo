#include <nigf.hpp>
#include <nidm.hpp>

#include "renderer.hpp"
#include "player.hpp"

#include <GL/gl.h>

#include <iostream>
#include <deque>
#include <stack>

nidm::AnimationManager animations;
nidm::GameObjectManager gameobjects;
nidm::GameSpiriteManager gamespirites;
nidm::MessageManager messages;

static nie::Renderer renderer(60);

static void on_draw()
{
    gameobjects.foreach ([](nigf::GameObject &go)
                         {
        renderer.setDrawingSquare(256, 256, go.get_position_x(), go.get_position_y(), go.get_position_z(), go.get_size_w(), go.get_size_h());
        renderer.setDrawingTexture(go.get_current_image());
        renderer.draw(); });
}

static void deliever_msg_to_hooks()
{
    messages.foreach ([&](auto &msg)
                      { gamespirites.foreach ([&](nigf::GameSpirite &spirite)
                                              { spirite.on_hook(*msg); }); });
}

static void clear_msgs()
{
    messages.clear();
}

static void on_tick()
{
    // computing tick
    deliever_msg_to_hooks();
    clear_msgs();
    gamespirites.foreach ([](nigf::GameSpirite &spirite)
                          { spirite.on_tick(); });
}

static void pack_message_up(std::shared_ptr<nigf::Message> msg)
{
    messages.add(msg);
}

nigf::GameObject obj_player(0, 0, "obj_player");
nigf::GameSpirite spr_player(0, "spr_player");
nigf::Animation ani_player(0, "ani_player", 800, {std::make_shared<nigf::Image>("../resource/minami_walk_down_0.jpg"),std::make_shared<nigf::Image>("../resource/minami_walk_down_1.jpg"), std::make_shared<nigf::Image>("../resource/error.jpg")});
//nigf::Animation ani_player(0, "ani_player", 200, {std::make_shared<nigf::Image>("../resource/minami_walk_down_0.png"),std::make_shared<nigf::Image>("../resource/minami_walk_down_1.png"), std::make_shared<nigf::Image>("../resource/error.png")});
int main(int argc, char *argv[]) noexcept
{
    std::cout << "hello world\n";

    animations.add(ani_player);
    obj_player.set_animation(animations.get("ani_player"));

    // initialize_demo();
    obj_player.set_size_h(200);
    obj_player.set_size_w(200);
    spr_player.bind_on_tick_func([&](nigf::GameObject &self)
                                 {
        if(self.get_position_y() > 256) self.set_position_y(self.get_position_y() - 1);
        if(self.get_position_y() - self.get_size_h() < -256) self.set_position_y(self.get_position_y() + 1);
        if(self.get_position_x() < -256) self.set_position_x(self.get_position_x() + 1);
        if(self.get_position_x() + self.get_size_w() > 256) self.set_position_x(self.get_position_x() - 1);

        self.set_position_x(self.get_position_x() + self.get_speed_x());
        self.set_position_y(self.get_position_y() + self.get_speed_y()); });
    spr_player.add_hook([&](nigf::Message *msg)
                        {
        if (msg->get_type() == nigf::MessageType::keyboard_msg)
        {
            auto buffer = static_cast<nigf::KeyboardMessage*>(msg);
            auto &obj = gameobjects.get(0);

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
        } });

    gameobjects.add(obj_player);
    spr_player.bind_gameobject(gameobjects.get(0));
    gamespirites.add(spr_player);

    nigf::Gameplay gp("hello world!", 800, 600, 60, &argc, argv);
    gp.bind_on_draw_func(on_draw);
    gp.bind_message_handle_func(pack_message_up);
    gp.bind_on_gameplay_tick_func(on_tick);
    nigf::current_gameplay = &gp;

    if (!gp.main_loop())
    {
        std::cerr << "Gameplay error: " << gp.get_error_msg() << '\n';
        return -1;
    }

    return 0;
}