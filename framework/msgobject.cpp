#include "msgobject.hpp"

nigf::Message::Message(MessageType mtype)
    : msg_type(mtype)
{
}

nigf::Message::~Message()
{
}

nigf::KeyboardMessage::KeyboardMessage(nigf::KeyboardCode key, bool down)
    : code(key), key_down(down), Message(MessageType::keyboard_msg)
{
}

nigf::KeyboardMessage::~KeyboardMessage()
{
}

const nigf::KeyboardCode nigf::KeyboardMessage::get_code()
{
    return code;
}

const bool nigf::KeyboardMessage::is_key_down()
{
    return key_down;
}

nigf::MouseMessage::MouseMessage(int x, int y, bool down)
    : position_x(x), position_y(y), mouse_down(down), Message(MessageType::mouse_msg)
{
}

nigf::MouseMessage::~MouseMessage()
{
}

const int nigf::MouseMessage::get_position_x()
{
    return position_x;
}

const int nigf::MouseMessage::get_position_y()
{
    return position_y;
}

const bool nigf::MouseMessage::is_mouse_down()
{
    return mouse_down;
}

nigf::CommonMessage::CommonMessage(int tid, const char *str)
    : type_id(tid), data(str), Message(MessageType::common_msg)
{
}

nigf::CommonMessage::~CommonMessage()
{
}

const int nigf::CommonMessage::get_type_id()
{
    return type_id;
}

std::string_view nigf::CommonMessage::get_data()
{
    return data;
}

const nigf::MessageType nigf::Message::get_type()
{
    return msg_type;
}