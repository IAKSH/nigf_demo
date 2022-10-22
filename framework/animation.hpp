#pragma once
#include "image.hpp"
#include <vector>
#include <memory>
#include <string>
#include <initializer_list>

namespace nigf
{
    class Animation
    {
    private:
        const int ID;
        const unsigned int FRAME_COUNT;
        const std::string NAME;
        std::vector<std::shared_ptr<Image>> frames;

    public:
        Animation(int id, const char *name, std::initializer_list<Image *> images);
        ~Animation();

        const unsigned int get_id();
        const unsigned int get_frame_count();
        nigf::Image &get_frame(int index);
    };
}