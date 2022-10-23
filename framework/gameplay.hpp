#pragma once
#include <functional>
#include <memory>
#include <string>
#include <string_view>

#include <GLFW/glfw3.h>

#include "msgobject.hpp"
#include "keyboard.hpp"

namespace nigf
{
    class Gameplay
    {
    private:
        const unsigned int aim_tps;
        const char *window_title;
        const int window_size_w, window_size_h;
        std::string error_msg;
        GLFWwindow *window = nullptr;

        std::function<void(std::shared_ptr<nigf::Message> msg)> message_handle_func = nullptr;
        std::function<void()> on_gameplay_tick_func = nullptr;
        std::function<void()> draw_func = nullptr;

        void initialize(int *argc, char *argv[]);
        void resize(GLFWwindow* win,GLsizei width, GLsizei height);
        void input_message_forward();
        void clearn_screen();
        void flush();
        void display();

    public:
        Gameplay(const char *title, int w, int h, unsigned int tps, int *argc, char *argv[]);
        ~Gameplay();

        void bind_message_handle_func(std::function<void(std::shared_ptr<nigf::Message> msg)> f);
        void bind_on_gameplay_tick_func(std::function<void()> func);
        void bind_on_draw_func(std::function<void()> func);
        bool main_loop();
        std::string_view get_error_msg();
    };
}