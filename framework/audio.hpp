#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <fstream>
#include <array>

#include <cstdint>

namespace nigf
{
    class Audio
    {
    private:
        const int ID;
        const std::string NAME;
        unsigned char *pcm;
        int size;

        int getFileCursorMark(std::ifstream &fs, std::string mark);

    public:
        Audio(int id, const char *name);
        Audio(int id, const char *name, const char *path);
        ~Audio();

        void reload(const char *path);
        int get_size();
        unsigned char *get_pcm();
        const std::string_view get_name();
    };
}