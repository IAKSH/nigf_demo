#include <nigf.hpp>
#include <nidm.hpp>
#include <renderer.hpp>

#include <GL/gl.h>

#include <iostream>
#include <deque>
#include <stack>

// custom
#include <player.hpp>
#include <background.hpp>
#include <sunflower.hpp>

nidm::AnimationManager animations;
nidm::GameObjectManager gameobjects;
nidm::GameSpiriteManager gamespirites;
nidm::MessageManager messages;

static nie::Renderer renderer(60);

static void on_draw()
{
    gameobjects.foreach ([](nigf::GameObject &go)
                         {
        renderer.setDrawingSquare(512, 512, go.get_position_x(), go.get_position_y(), go.get_position_z(), go.get_size_w(), go.get_size_h());
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

int main(int argc, char *argv[]) noexcept
{
    std::cout << "hello world\n";

    mydemo::player::initialize(animations,gameobjects,gamespirites,messages);
    mydemo::sunflower::initialize(animations,gameobjects,gamespirites,messages);
    mydemo::background::initialize(animations,gameobjects,gamespirites,messages);

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