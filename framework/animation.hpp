#pragma once
#include "image.hpp"
#include <vector>
#include <memory>
#include <string>
#include <initializer_list>

namespace nigf
{
    inline nigf::Image error_image("../resource/error.png");

    class Animation
    {
    private:
        const int ID;
        const unsigned int FRAME_COUNT;
        const unsigned int INTERVAL_MS;
        const std::string NAME;
        std::vector<std::shared_ptr<Image>> frames;

    public:
        Animation(int id, const char *name, int interval, std::initializer_list<std::shared_ptr<nigf::Image>> images);
        ~Animation();

        const unsigned int get_id();
        const unsigned int get_interval_ms();
        const unsigned int get_frame_count();
        nigf::Image &get_frame(int index);
        const std::string_view get_name();
    };
}