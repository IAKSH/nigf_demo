#include <nigf.hpp>
#include <nidm.hpp>

#include "renderer.hpp"
#include "player.hpp"

#include <GL/gl.h>
#include <GL/freeglut.h>

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
    renderer.clear();
    gameobjects.foreach([](nigf::GameObject &go)
    {
        renderer.setDrawingSquare(256, 256, go.get_position_x(), go.get_position_y(), go.get_position_z(), go.get_size_w(), go.get_size_h());
        renderer.setDrawingTexture(go.get_current_image());
        renderer.draw();
    });
    renderer.swap();
}

static void deliever_msg_to_hooks()
{
    messages.foreach([&](auto &msg)
    {
        gamespirites.foreach([&](nigf::GameSpirite &spirite)
        {
            spirite.on_hook(*msg);
        });
    });
}

static void clear_msgs()
{
    messages.clear();
}

static void on_tick(int id)
{
    // computing tick
    deliever_msg_to_hooks();
    clear_msgs();
    gamespirites.foreach([](nigf::GameSpirite &spirite)
    {
        spirite.on_tick();
    });

    // renderer frame
    on_draw();

    glutTimerFunc(16, on_tick, id);
}

static void on_resize(GLsizei width, GLsizei height)
{
    renderer.openGLResize(width, height);
}

static void mouse_msg_delive(int x, int y)
{
    messages.add(std::make_shared<nigf::MouseMessage>(nigf::MouseMessage(x, y, false)));
}

static void keyboard_down_msg_delive(unsigned char c, int x, int y)
{
    messages.add(std::make_shared<nigf::KeyoardMessage>(nigf::KeyoardMessage(c, true)));
    mouse_msg_delive(x, y);
}

static void keyboard_up_msg_delive(unsigned char c, int x, int y)
{
    messages.add(std::make_shared<nigf::KeyoardMessage>(nigf::KeyoardMessage(c, false)));
    mouse_msg_delive(x, y);
}

static void initialize_demo()
{
    demo::initialize();
    
    //_gameobjects.push_back(demo::obj_player);
    //_gamespirites.push_back(demo::spr_player);
}


nigf::GameObject obj_player(0,0,"obj_player");
nigf::GameSpirite spr_player(0,"spr_player");

int main(int argc, char *argv[]) noexcept
{
    std::cout << "hello world\n";

    //initialize_demo();
    obj_player.set_size_h(100);
    obj_player.set_size_w(100);
    spr_player.bind_on_tick_func([&](nigf::GameObject& self)
    {
        if(self.get_position_y() >= 256) self.set_speed_y(-1);
        if(self.get_position_y() - self.get_size_h() <= -256) self.set_speed_y(1);
        if(self.get_position_x() <= -256) self.set_speed_x(1);
        if(self.get_position_x() + self.get_size_w() >= 256) self.set_speed_x(-1);

        self.set_position_x(self.get_position_x() + self.get_speed_x());
        self.set_position_y(self.get_position_y() + self.get_speed_y());
    });
    spr_player.add_hook([&](nigf::Message* msg)
    {
        if (msg->get_type() == nigf::MessageType::keyboard_msg)
        {
            auto buffer = static_cast<nigf::KeyoardMessage*>(msg);
            auto &obj = gameobjects.get(0);
            if (buffer->is_key_down())
            {
                switch (buffer->get_ascii())
                {
                case 'w':
                    obj.set_speed_y(1);
                    break;

                case 'a':
                    obj.set_speed_x(-1);
                    break;

                case 's':
                    obj.set_speed_y(-1);
                    break;

                case 'd':
                    obj.set_speed_x(1);
                    break;
                }
            }
            else 
            {
                switch (buffer->get_ascii())
                {
                case 'w':
                    obj.set_speed_y(0);
                    break;

                case 'a':
                    obj.set_speed_x(0);
                    break;

                case 's':
                    obj.set_speed_y(0);
                    break;

                case 'd':
                    obj.set_speed_x(0);
                    break;
                }
            }
        }
    });

    gameobjects.add(obj_player);
    spr_player.bind_gameobject(gameobjects.get(0));
    gamespirites.add(spr_player);

    nigf::Gameplay gp("hello world!", 800, 600, 60, &argc, argv);
    gp.bind_ondraw(on_draw);
    gp.bind_onresize(on_resize);
    gp.bind_onkeyboard_down(keyboard_down_msg_delive);
    gp.bind_onkeyboard_up(keyboard_up_msg_delive);
    gp.bind_ontick(on_tick);

    if (!gp.main_loop())
    {
        std::cerr << "Gameplay error: " << gp.get_error_msg() << '\n';
        return -1;
    }

    return 0;
}