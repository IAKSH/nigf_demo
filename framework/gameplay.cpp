#include "gameplay.hpp"
#include <GL/freeglut.h>

void nigf::Gameplay::initialize(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(300, 300);
    glutInitWindowSize(window_size_w, window_size_h);
    glutCreateWindow(window_title);
}

nigf::Gameplay::Gameplay(const char *title, int w, int h, unsigned int tps, int *argc, char *argv[])
    : window_title(title), window_size_w(w), window_size_h(h), aim_tps(tps)
{
    initialize(argc, argv);
}

nigf::Gameplay::~Gameplay() {}

void nigf::Gameplay::bind_ondraw(void (*func)(void))
{
    on_draw_callback = func;
}

void nigf::Gameplay::bind_onresize(void (*func)(int, int))
{
    on_resize_callback = func;
}

void nigf::Gameplay::bind_onkeyboard_down(void (*func)(unsigned char, int, int))
{
    on_keyboard_down_callback = func;
}

void nigf::Gameplay::bind_onkeyboard_up(void (*func)(unsigned char, int, int))
{
    on_keyboard_up_callback = func;
}

void nigf::Gameplay::bind_ontick(void (*func)(int))
{
    on_tick_callback = func;
}

bool nigf::Gameplay::main_loop()
{
    if (!on_draw_callback || !on_resize_callback)
    {
        error_msg = "missing neccessary callback binding";
        return false;
    }

    glutDisplayFunc(on_draw_callback);
    glutReshapeFunc(on_resize_callback);
    if (on_keyboard_down_callback)
        glutKeyboardFunc(on_keyboard_down_callback);
    if (on_keyboard_up_callback)
        glutKeyboardUpFunc(on_keyboard_up_callback);
    if (on_tick_callback)
        glutTimerFunc(static_cast<int>(1.0f / aim_tps), on_tick_callback, 0);
    glutMainLoop();
    return true;
}

std::string_view nigf::Gameplay::get_error_msg()
{
    return error_msg;
}