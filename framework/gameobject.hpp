#pragma once
#include "animation.hpp"
#include <string>
#include <unordered_map>

namespace nigf
{
    // GameObject is what you actually saw in game,
    // it contains position data, and some basical infomation of this "Object".
    // The division between data and logic can reduce function call in each tick, which is benificial to performance.
    // each GameObject will be called by renderer
    class GameObject
    {
    private:
        int position_x,position_y,position_z;
        int speed_x,speed_y,speed_z;
        int size_w,size_h;
        int current_frame_index = 0;
        unsigned int id;
        const unsigned int TEMPLATE_ID;
        const std::string NAME;
        std::unordered_map<std::string,std::string> datas;
        std::shared_ptr<nigf::Animation> current_animation = nullptr;

    public:
        GameObject(unsigned int id,unsigned int tid,const char* name);
        ~GameObject();
        
        int get_position_x();
        int get_position_y();
        int get_position_z();
        int get_speed_x();
        int get_speed_y();
        int get_speed_z();
        int get_size_w();
        int get_size_h();
        unsigned int get_id();
        const unsigned int get_template_id();
        void reset_id(unsigned int new_id);
        void set_position_x(int x);
        void set_position_y(int y);
        void set_position_z(int z);
        void set_speed_x(int speed);
        void set_speed_y(int speed);
        void set_speed_z(int speed);
        void set_size_w(int w);
        void set_size_h(int h);
        void set_animation(nigf::Animation& animation);
        void add_data(const char* key);
        void set_data(const char* key,const char* val);
        std::string_view get_name();
        std::string_view get_data(const char* key);
        nigf::Image& get_current_image();
    };
}