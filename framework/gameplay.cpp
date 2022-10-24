#include "gameplay.hpp"
#include <iostream>
#include <array>
#include <set>

void nigf::Gameplay::initialize(int *argc, char *argv[])
{
    glfwInit();
    // using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // not core mod, for I'm not realy good at it.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    // for MacOS only
#ifdef MAC_OS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(window_size_h, window_size_w, window_title, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "[ERROR] nigf::Gameplay::initialize() failed, can't create GLFWwindow\n";
        glfwTerminate();
        exit(-1);
    }
}

nigf::Gameplay::Gameplay(const char *title, int w, int h, unsigned int tps, int *argc, char *argv[])
    : window_title(title), window_size_w(w), window_size_h(h), aim_tps(tps)
{
    initialize(argc, argv);
}

nigf::Gameplay::~Gameplay()
{
    glfwTerminate();
}

void nigf::Gameplay::resize(GLFWwindow *win, GLsizei width, GLsizei height)
{
    glViewport(0, 0, window_size_w, window_size_h);
}

void nigf::Gameplay::input_message_forward(int key, int scancode, int action, int mods)
{
    // int key:      | same as static_cast<int>(GLFW_KEY_XXX)   |                       |
    // int scancode: | unknow yet                               |                       |
    // int action:   | 0->release                               | 1->push               | 2->keeping push
    // mods:         | 0->not hold with shift                   | 1->hold with shift 1  |

    // debug
    // std::cout << key << '\t' << scancode << '\t' << action << '\t' << mods << '\n';

    using nigf::KeyboardCode;
    if (!message_handle_func)
        return;

    if (action == 2) message_handle_func(std::make_shared<nigf::KeyboardMessage>(static_cast<nigf::KeyboardCode>(key), true));
    else if (action == 1) message_handle_func(std::make_shared<nigf::KeyboardMessage>(static_cast<nigf::KeyboardCode>(key), true));
    else if (action == 0) message_handle_func(std::make_shared<nigf::KeyboardMessage>(static_cast<nigf::KeyboardCode>(key), false));
}

void nigf::Gameplay::bind_message_handle_func(std::function<void(std::shared_ptr<nigf::Message> msg)> f)
{
    message_handle_func = f;
}

void nigf::Gameplay::bind_on_gameplay_tick_func(std::function<void()> func)
{
    on_gameplay_tick_func = func;
}

void nigf::Gameplay::bind_on_draw_func(std::function<void()> func)
{
    draw_func = func;
}

void nigf::Gameplay::clearn_screen()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void nigf::Gameplay::display()
{
    clearn_screen();
    if (draw_func)
        draw_func();
}

static void glfw_key_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
    if (!nigf::current_gameplay)
    {
        std::cerr << "[ERROR] nigf::current_gameplay is null\n";
        abort();
    }

    nigf::current_gameplay->input_message_forward(key, scancode, action, mods);
}

bool nigf::Gameplay::main_loop()
{
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, glfw_key_callback);

    while (!glfwWindowShouldClose(window))
    {
        if (on_gameplay_tick_func)
            on_gameplay_tick_func();
        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return true;
}

std::string_view nigf::Gameplay::get_error_msg()
{
    return error_msg;
}