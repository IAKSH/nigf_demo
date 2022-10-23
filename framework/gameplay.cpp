#include "gameplay.hpp"
#include <iostream>
#include <array>

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

void nigf::Gameplay::input_message_forward()
{
    using nigf::KeyboardCode;
    if (!message_handle_func)
        return;
    std::array<KeyboardCode,97> listening_keys =
        {
            KeyboardCode::KEY_0, KeyboardCode::KEY_1, KeyboardCode::KEY_2, KeyboardCode::KEY_3, KeyboardCode::KEY_4, KeyboardCode::KEY_5,
            KeyboardCode::KEY_6, KeyboardCode::KEY_7, KeyboardCode::KEY_8, KeyboardCode::KEY_9, KeyboardCode::KEY_A, KeyboardCode::KEY_B,
            KeyboardCode::KEY_C, KeyboardCode::KEY_D, KeyboardCode::KEY_E, KeyboardCode::KEY_F, KeyboardCode::KEY_G, KeyboardCode::KEY_H,
            KeyboardCode::KEY_I, KeyboardCode::KEY_J, KeyboardCode::KEY_K, KeyboardCode::KEY_L, KeyboardCode::KEY_M, KeyboardCode::KEY_N,
            KeyboardCode::KEY_O, KeyboardCode::KEY_P, KeyboardCode::KEY_Q, KeyboardCode::KEY_R, KeyboardCode::KEY_S, KeyboardCode::KEY_T,
            KeyboardCode::KEY_U, KeyboardCode::KEY_V, KeyboardCode::KEY_W, KeyboardCode::KEY_X, KeyboardCode::KEY_Y, KeyboardCode::KEY_Z,
            KeyboardCode::KEY_SPACE,
            KeyboardCode::KEY_LEFT_BRACKET,
            KeyboardCode::KEY_BACKSLASH,
            KeyboardCode::KEY_RIGHT_BRACKET,
            KeyboardCode::KEY_ESCAPE,
            KeyboardCode::KEY_ENTER,
            KeyboardCode::KEY_TAB,
            KeyboardCode::KEY_BACKSPACE,
            KeyboardCode::KEY_INSERT,
            KeyboardCode::KEY_DELETE,
            KeyboardCode::KEY_RIGHT,
            KeyboardCode::KEY_LEFT,
            KeyboardCode::KEY_DOWN,
            KeyboardCode::KEY_UP,
            KeyboardCode::KEY_PAGE_UP,
            KeyboardCode::KEY_PAGE_DOWN,
            KeyboardCode::KEY_HOME,
            KeyboardCode::KEY_END,
            KeyboardCode::KEY_CAPS_LOCK,
            KeyboardCode::KEY_SCROLL_LOCK,
            KeyboardCode::KEY_NUM_LOCK,
            KeyboardCode::KEY_PRINT_SCREEN,
            KeyboardCode::KEY_PAUSE,
            KeyboardCode::KEY_F1, KeyboardCode::KEY_F2, KeyboardCode::KEY_F3, KeyboardCode::KEY_F4, KeyboardCode::KEY_F5, KeyboardCode::KEY_F6, KeyboardCode::KEY_F7,
            KeyboardCode::KEY_F8, KeyboardCode::KEY_F9, KeyboardCode::KEY_F10, KeyboardCode::KEY_F11, KeyboardCode::KEY_F12,
            KeyboardCode::KEY_KP_0, KeyboardCode::KEY_KP_1, KeyboardCode::KEY_KP_2, KeyboardCode::KEY_KP_3, KeyboardCode::KEY_KP_4, KeyboardCode::KEY_KP_5,
            KeyboardCode::KEY_KP_6, KeyboardCode::KEY_KP_7, KeyboardCode::KEY_KP_8, KeyboardCode::KEY_KP_9,
            KeyboardCode::KEY_KP_DECIMAL,
            KeyboardCode::KEY_KP_DIVIDE,
            KeyboardCode::KEY_KP_MULTIPLY,
            KeyboardCode::KEY_KP_SUBTRACT,
            KeyboardCode::KEY_KP_ADD,
            KeyboardCode::KEY_KP_ENTER,
            KeyboardCode::KEY_KP_EQUAL,
            KeyboardCode::KEY_LEFT_SHIFT,
            KeyboardCode::KEY_LEFT_CONTROL,
            KeyboardCode::KEY_LEFT_ALT,
            KeyboardCode::KEY_LEFT_SUPER,
            KeyboardCode::KEY_RIGHT_SHIFT,
            KeyboardCode::KEY_RIGHT_CONTROL,
            KeyboardCode::KEY_RIGHT_ALT,
            KeyboardCode::KEY_RIGHT_SUPER,
            KeyboardCode::KEY_MENU
        };

    for (auto &item : listening_keys)
    {
        if (glfwGetKey(window, static_cast<int>(item)) == GLFW_PRESS)
        {
            message_handle_func(std::make_shared<nigf::KeyboardMessage>(item, true));
            continue;
        }
        else if (glfwGetKey(window, static_cast<int>(item)) == GLFW_RELEASE)
        {
            message_handle_func(std::make_shared<nigf::KeyboardMessage>(item, false));
            continue;
        }
    }
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
    glClear(GL_COLOR_BUFFER_BIT);
}

void nigf::Gameplay::display()
{
    clearn_screen();
    if (draw_func)
        draw_func();
}

bool nigf::Gameplay::main_loop()
{
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        input_message_forward();
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