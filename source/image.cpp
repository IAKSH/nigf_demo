#include "image.hpp"

extern "C"
{
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"
}

nigf::Image::Image() {}

nigf::Image::Image(const char *path)
{
    open(path);
}

nigf::Image::~Image()
{
    stbi_image_free(data);
}

void nigf::Image::open(const char *path)
{
    if (data)
        stbi_image_free(data);
    data = stbi_load(path, &width, &hight, &channel_count, 0);
}

void nigf::Image::resize(int new_width, int new_hight)
{
    uint8_t *new_data = new uint8_t[new_width * new_hight * channel_count];
    stbir_resize(data, width, hight, 0, new_data, new_width, new_hight, 0, STBIR_TYPE_UINT8, channel_count, STBIR_ALPHA_CHANNEL_NONE, 0,
                 STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP,
                 STBIR_FILTER_BOX, STBIR_FILTER_BOX,
                 STBIR_COLORSPACE_SRGB, nullptr);
    stbi_image_free(data);
    data = new_data;
    width = new_width;
    hight = new_hight;
}

void nigf::Image::save(const char *path)
{
    stbi_write_png(path, width, hight, channel_count, data, 0);
}

unsigned char *nigf::Image::getData()
{
    return data;
}

int nigf::Image::getWidth()
{
    return width;
}

int nigf::Image::getHight()
{
    return hight;
}

int nigf::Image::getChannelCount()
{
    return channel_count;
}