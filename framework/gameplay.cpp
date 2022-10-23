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

void nigf::Gameplay::input_message_forward()
{
    using nigf::KeyboardCode;
    if (!message_handle_func)
        return;
    static std::array<std::pair<KeyboardCode,bool>,97> listening_keys =
        {
            std::pair(KeyboardCode::KEY_0, false), std::pair(KeyboardCode::KEY_1, false), std::pair(KeyboardCode::KEY_2, false), std::pair(KeyboardCode::KEY_3, false), std::pair(KeyboardCode::KEY_4, false), std::pair(KeyboardCode::KEY_5, false),
            std::pair(KeyboardCode::KEY_6, false), std::pair(KeyboardCode::KEY_7, false), std::pair(KeyboardCode::KEY_8, false), std::pair(KeyboardCode::KEY_9, false), std::pair(KeyboardCode::KEY_A, false), std::pair(KeyboardCode::KEY_B, false),
            std::pair(KeyboardCode::KEY_C, false), std::pair(KeyboardCode::KEY_D, false), std::pair(KeyboardCode::KEY_E, false), std::pair(KeyboardCode::KEY_F, false), std::pair(KeyboardCode::KEY_G, false), std::pair(KeyboardCode::KEY_H, false),
            std::pair(KeyboardCode::KEY_I, false), std::pair(KeyboardCode::KEY_J, false), std::pair(KeyboardCode::KEY_K, false), std::pair(KeyboardCode::KEY_L, false), std::pair(KeyboardCode::KEY_M, false), std::pair(KeyboardCode::KEY_N, false),
            std::pair(KeyboardCode::KEY_O, false), std::pair(KeyboardCode::KEY_P, false), std::pair(KeyboardCode::KEY_Q, false), std::pair(KeyboardCode::KEY_R, false), std::pair(KeyboardCode::KEY_S, false), std::pair(KeyboardCode::KEY_T, false),
            std::pair(KeyboardCode::KEY_U, false), std::pair(KeyboardCode::KEY_V, false), std::pair(KeyboardCode::KEY_W, false), std::pair(KeyboardCode::KEY_X, false), std::pair(KeyboardCode::KEY_Y, false), std::pair(KeyboardCode::KEY_Z, false),
            std::pair(KeyboardCode::KEY_SPACE, false),
            std::pair(KeyboardCode::KEY_LEFT_BRACKET, false),
            std::pair(KeyboardCode::KEY_BACKSLASH, false),
            std::pair(KeyboardCode::KEY_RIGHT_BRACKET, false),
            std::pair(KeyboardCode::KEY_ESCAPE, false),
            std::pair(KeyboardCode::KEY_ENTER, false),
            std::pair(KeyboardCode::KEY_TAB, false),
            std::pair(KeyboardCode::KEY_BACKSPACE, false),
            std::pair(KeyboardCode::KEY_INSERT, false),
            std::pair(KeyboardCode::KEY_DELETE, false),
            std::pair(KeyboardCode::KEY_RIGHT, false),
            std::pair(KeyboardCode::KEY_LEFT, false),
            std::pair(KeyboardCode::KEY_DOWN, false),
            std::pair(KeyboardCode::KEY_UP, false),
            std::pair(KeyboardCode::KEY_PAGE_UP, false),
            std::pair(KeyboardCode::KEY_PAGE_DOWN, false),
            std::pair(KeyboardCode::KEY_HOME, false),
            std::pair(KeyboardCode::KEY_END, false),
            std::pair(KeyboardCode::KEY_CAPS_LOCK, false),
            std::pair(KeyboardCode::KEY_SCROLL_LOCK, false),
            std::pair(KeyboardCode::KEY_NUM_LOCK, false),
            std::pair(KeyboardCode::KEY_PRINT_SCREEN, false),
            std::pair(KeyboardCode::KEY_PAUSE, false),
            std::pair(KeyboardCode::KEY_F1, false), std::pair(KeyboardCode::KEY_F2, false), std::pair(KeyboardCode::KEY_F3, false), std::pair(KeyboardCode::KEY_F4, false), std::pair(KeyboardCode::KEY_F5, false), std::pair(KeyboardCode::KEY_F6, false), std::pair(KeyboardCode::KEY_F7, false),
            std::pair(KeyboardCode::KEY_F8, false), std::pair(KeyboardCode::KEY_F9, false), std::pair(KeyboardCode::KEY_F10, false), std::pair(KeyboardCode::KEY_F11, false), std::pair(KeyboardCode::KEY_F12, false),
            std::pair(KeyboardCode::KEY_KP_0, false), std::pair(KeyboardCode::KEY_KP_1, false), std::pair(KeyboardCode::KEY_KP_2, false), std::pair(KeyboardCode::KEY_KP_3, false), std::pair(KeyboardCode::KEY_KP_4, false), std::pair(KeyboardCode::KEY_KP_5, false),
            std::pair(KeyboardCode::KEY_KP_6, false), std::pair(KeyboardCode::KEY_KP_7, false), std::pair(KeyboardCode::KEY_KP_8, false), std::pair(KeyboardCode::KEY_KP_9, false),
            std::pair(KeyboardCode::KEY_KP_DECIMAL, false),
            std::pair(KeyboardCode::KEY_KP_DIVIDE, false),
            std::pair(KeyboardCode::KEY_KP_MULTIPLY, false),
            std::pair(KeyboardCode::KEY_KP_SUBTRACT, false),
            std::pair(KeyboardCode::KEY_KP_ADD, false),
            std::pair(KeyboardCode::KEY_KP_ENTER, false),
            std::pair(KeyboardCode::KEY_KP_EQUAL, false),
            std::pair(KeyboardCode::KEY_LEFT_SHIFT, false),
            std::pair(KeyboardCode::KEY_LEFT_CONTROL, false),
            std::pair(KeyboardCode::KEY_LEFT_ALT, false),
            std::pair(KeyboardCode::KEY_LEFT_SUPER, false),
            std::pair(KeyboardCode::KEY_RIGHT_SHIFT, false),
            std::pair(KeyboardCode::KEY_RIGHT_CONTROL, false),
            std::pair(KeyboardCode::KEY_RIGHT_ALT, false),
            std::pair(KeyboardCode::KEY_RIGHT_SUPER, false),
            std::pair(KeyboardCode::KEY_MENU, false)
        };

    for (auto &item : listening_keys)
    {
        auto &fist = item.first;
        auto &second = item.second;

        if (!second && glfwGetKey(window, static_cast<int>(fist)) == GLFW_PRESS)
        {
            second = true;
            message_handle_func(std::make_shared<nigf::KeyboardMessage>(fist, true));
            continue;
        }
        if (second && glfwGetKey(window, static_cast<int>(fist)) == GLFW_RELEASE)
        {
            second = false;
            message_handle_func(std::make_shared<nigf::KeyboardMessage>(fist, false));
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