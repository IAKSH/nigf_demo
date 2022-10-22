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

        unsigned char *getData();
        void open(const char *path);
        void resize(int new_width, int new_hight);
        void save(const char *path);
        int getWidth();
        int getHight();
        int getChannelCount();
    };
}
