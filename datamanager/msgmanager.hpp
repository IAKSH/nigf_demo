#pragma once

#include "objmanager.hpp"
#include <memory>

namespace nidm
{
    class MessageManager : public ObjectManager<std::shared_ptr<nigf::Message>>
    {
    private:
        std::forward_list<std::shared_ptr<nigf::Message>> list;
        unsigned int count = 0;

    public:
        MessageManager();
        ~MessageManager();
    };
}