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

void nigf::Gameplay::bind_ondraw(on_draw_func func)
{
    ondraw_callback = func;
}

void nigf::Gameplay::bind_onresize(on_resize_func func)
{
    onresize_callback = func;
}

void nigf::Gameplay::bind_onkeyboard_down(on_keyboard_func func)
{
    onkeyboard_down_callback = func;
}

void nigf::Gameplay::bind_onkeyboard_up(on_keyboard_func func)
{
    onkeyboard_up_callback = func;
}

void nigf::Gameplay::bind_ontick(on_tick_func func)
{
    ontick_callback = func;
}

bool nigf::Gameplay::main_loop()
{
    if (!ondraw_callback || !onresize_callback)
    {
        error_msg = "missing neccessary callback binding";
        return false;
    }

    glutDisplayFunc(*ondraw_callback.target<void (*)()>());
    glutReshapeFunc(*onresize_callback.target<void (*)(int, int)>());
    if (onkeyboard_down_callback)
        glutKeyboardFunc(*onkeyboard_down_callback.target<void (*)(unsigned char, int, int)>());
    if (onkeyboard_up_callback)
        glutKeyboardUpFunc(*onkeyboard_up_callback.target<void (*)(unsigned char, int, int)>());
    if (ontick_callback)
        glutTimerFunc(static_cast<int>(1.0f / aim_tps), *ontick_callback.target<void (*)(int)>(), 0);
    glutMainLoop();
    return true;
}

std::string_view nigf::Gameplay::get_error_msg()
{
    return error_msg;
}