#pragma once
#include <functional>
#include <string>
#include <string_view>

namespace nigf
{
    class Gameplay
    {
        using on_draw_func = std::function<void(void)>;
        using on_resize_func = std::function<void(int, int)>;
        using on_keyboard_func = std::function<void(unsigned char, int, int)>;
        using on_tick_func = std::function<void(int)>;

    private:
        const unsigned int aim_tps;
        const char *window_title;
        const int window_size_w, window_size_h;
        std::string error_msg;
        on_draw_func ondraw_callback = nullptr;
        on_resize_func onresize_callback = nullptr;
        on_keyboard_func onkeyboard_down_callback = nullptr;
        on_keyboard_func onkeyboard_up_callback = nullptr;
        on_tick_func ontick_callback = nullptr;

        void initialize(int *argc, char *argv[]);

    public:
        Gameplay(const char *title, int w, int h, unsigned int tps, int *argc, char *argv[]);
        ~Gameplay();

        void bind_ondraw(on_draw_func func);
        void bind_onresize(on_resize_func func);
        void bind_onkeyboard_down(on_keyboard_func func);
        void bind_onkeyboard_up(on_keyboard_func func);
        void bind_ontick(on_tick_func func);
        bool main_loop();
        std::string_view get_error_msg();
    };
}