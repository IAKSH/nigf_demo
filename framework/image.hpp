#pragma once

namespace nigf
{
    class Image
    {
    private:
        unsigned char *data = nullptr;
        int width, hight, channel_count;

    public:
        Image();
        Image(const char *path);
        ~Image();

        unsigned char *get_data();
        void open(const char *path);
        void resize(int new_width, int new_hight);
        void save(const char *path);
        int get_width();
        int get_hight();
        int get_channel_count();
    };
}
