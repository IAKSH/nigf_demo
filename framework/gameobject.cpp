#include "gameobject.hpp"

nigf::GameObject::GameObject(unsigned int id, unsigned int tid, const char *name)
    : ID(id), TEMPLATE_ID(tid), NAME(name)
{
}

nigf::GameObject::~GameObject()
{
}

int nigf::GameObject::get_position_x()
{
    return position_x;
}

int nigf::GameObject::get_position_y()
{
    return position_y;
}

int nigf::GameObject::get_position_z()
{
    return position_z;
}

const unsigned int nigf::GameObject::get_id()
{
    return ID;
}

const unsigned int nigf::GameObject::get_template_id()
{
    return TEMPLATE_ID;
}

void nigf::GameObject::set_position_x(int x)
{
    position_x = x;
}

void nigf::GameObject::set_position_y(int y)
{
    position_y = y;
}

void nigf::GameObject::set_position_z(int z)
{
    position_z = z;
}

void nigf::GameObject::set_data(const char *key, const char *val)
{
    datas[key] = val;
}

void nigf::GameObject::add_data(const char *key)
{
    datas[key] = "[undifined]";
}

std::string_view nigf::GameObject::get_name()
{
    return NAME;
}

std::string_view nigf::GameObject::get_data(const char *key)
{
    return datas[key];
}

nigf::Image &nigf::GameObject::get_current_image()
{
    if (current_animation != nullptr)
    {
        auto &buffer = *current_animation;
        if (current_frame_index >= buffer.get_frame_count())
            current_frame_index = -1;

        return buffer.get_frame(current_frame_index);
    }
    else
        return nigf::error_image;
}

void nigf::GameObject::set_animation(nigf::Animation &animation)
{
    std::shared_ptr<nigf::Animation> ptr(&animation);
    current_animation = ptr;
}