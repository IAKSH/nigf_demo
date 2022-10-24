#include "gameobject.hpp"
#include <iostream>

nigf::GameObject::GameObject(unsigned int id, unsigned int tid, const char *name)
    : id(id), TEMPLATE_ID(tid), NAME(name)
{
    position_x = 0;
    position_y = 0;
    position_z = 0;
    size_h = 10;
    size_w = 10;
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

unsigned int nigf::GameObject::get_id()
{
    return id;
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
    auto &buffer = *current_animation;

    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - animation_last_swap_time).count() < current_animation->get_interval_ms())
    {
        return buffer.get_frame(current_frame_index);
    }

    animation_last_swap_time = now;

    if (current_frame_index++; current_animation != nullptr)
    {
        if (current_frame_index >= buffer.get_frame_count())
            current_frame_index = 0;

        return buffer.get_frame(current_frame_index);
    }
    else
        return error_image;
}

void nigf::GameObject::set_animation(nigf::Animation &animation)
{
    std::shared_ptr<nigf::Animation> ptr(&animation);
    current_animation = ptr;
}

int nigf::GameObject::get_size_w()
{
    return size_w;
}

int nigf::GameObject::get_size_h()
{
    return size_h;
}

void nigf::GameObject::set_size_w(int w)
{
    // Should use log system when nigf's log system is ready.
    if (w < 0)
        abort();
    size_w = w;
}

void nigf::GameObject::set_size_h(int h)
{
    // Should use log system when nigf's log system is ready.
    if (h < 0)
        abort();
    size_h = h;
}

void set_speed_x(int speed);
void set_speed_y(int speed);
void set_speed_z(int speed);

void nigf::GameObject::set_speed_x(int speed)
{
    speed_x = speed;
}

void nigf::GameObject::set_speed_y(int speed)
{
    speed_y = speed;
}

void nigf::GameObject::set_speed_z(int speed)
{
    speed_z = speed;
}

int nigf::GameObject::get_speed_x()
{
    return speed_x;
}

int nigf::GameObject::get_speed_y()
{
    return speed_y;
}

int nigf::GameObject::get_speed_z()
{
    return speed_z;
}

void nigf::GameObject::reset_id(unsigned int new_id)
{
    id = new_id;
}