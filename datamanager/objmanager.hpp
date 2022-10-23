#pragma once
#include <nigf.hpp>

#include <string>
#include <functional>
#include <list>
#include <iostream>

namespace nidm
{
    template <typename T>
    class ObjectManager
    {
    protected:
        std::list<T> list;
        unsigned int count = 0;

    public:
        ObjectManager() {}
        ~ObjectManager() {}

        unsigned int get_count()
        {
            return count;
        }

        // copy
        void add(T t)
        {
            count++;
            list.push_front(t);
        }

        void foreach (std::function<void(T &)> func)
        {
            for (auto &t : list)
                func(t);
        }

        T &get(unsigned int id)
        {
            for (auto &t : list)
                if (t.get_id() == id)
                    return t;
            std::cerr << "[ERROR] nidm::ObjectManager::get(unsigned int id) failed\n";
            exit(-1);
        }

        T &get(std::string name)
        {
            for (auto &t : list)
                if (t.get_name() == name)
                    return t;
            std::cerr << "[ERROR] nidm::ObjectManager::get(std::string name) failed\n";
            exit(-1);
        }

        void remove(unsigned int id)
        {
            list.remove_if([&](nigf::GameObject &go)
                           { go.get_id() == id; });
        }

        void remove(std::string name)
        {
            list.remove_if([&](nigf::GameObject &go)
                           { go.get_name() == name; });
        }

        void clear()
        {
            list.clear();
        }
    };
}