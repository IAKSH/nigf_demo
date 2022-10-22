#include "animation.hpp"

nigf::Animation::Animation(int id, const char *name, std::initializer_list<Image *> images)
    : ID(id), FRAME_COUNT(images.size()), NAME(name)
{
    for (auto &image : images)
    {
        std::shared_ptr<nigf::Image> ptr(image);
        frames.push_back(ptr);
    }
}

nigf::Animation::~Animation()
{
}

const unsigned int nigf::Animation::get_id()
{
    return ID;
}

const unsigned int nigf::Animation::get_frame_count()
{
    return FRAME_COUNT;
}

nigf::Image &nigf::Animation::get_frame(int index)
{
    return *(frames.at(index).get());
}