#pragma once

#include "objmanager.hpp"
#include <memory>

namespace nidm
{
    class MessageManager : public ObjectManager<std::shared_ptr<nigf::Message>>
    {
    public:
        MessageManager();
        ~MessageManager();
    };
}