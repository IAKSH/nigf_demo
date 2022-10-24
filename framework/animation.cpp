#include "animation.hpp"

nigf::Animation::Animation(int id, const char *name, int interval, std::initializer_list<std::shared_ptr<nigf::Image>> images)
    : ID(id), FRAME_COUNT(images.size()), NAME(name), INTERVAL_MS(interval)
{
    for (auto &image : images)
        frames.push_back(image);
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

const std::string_view nigf::Animation::get_name()
{
    return NAME;
}

const unsigned int nigf::Animation::get_interval_ms()
{
    return INTERVAL_MS;
}