#pragma once
#include <string>
#include <string_view>

#include "keyboard.hpp"

namespace nigf
{
    enum class MessageType
    {
        keyboard_msg,
        mouse_msg,
        error_msg,
        common_msg
    };

    class Message
    {
    private:
        const MessageType msg_type;

    public:
        Message(MessageType mtype);
        ~Message();

        const MessageType get_type();
    };

    class KeyboardMessage : public Message
    {
    private:
        const nigf::KeyboardCode code;
        const bool key_down;

    public:
        KeyboardMessage(nigf::KeyboardCode key, bool down);
        ~KeyboardMessage();

        const nigf::KeyboardCode get_code();
        const bool is_key_down();
    };

    class MouseMessage : public Message
    {
    private:
        const int position_x, position_y;
        const bool mouse_down;

    public:
        MouseMessage(int x, int y, bool down);
        ~MouseMessage();

        const int get_position_x();
        const int get_position_y();
        const bool is_mouse_down();
    };

    class CommonMessage : public Message
    {
    private:
        const int type_id;
        const std::string data;

    public:
        CommonMessage(int tid, const char *str);
        ~CommonMessage();
        
        const int get_type_id();
        std::string_view get_data();
    };
}