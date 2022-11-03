#pragma once
#include <image.hpp>
#include <GL/gl.h>

#include <array>

namespace nie
{
    class Renderer
    {
    private:
        nigf::Image* drawing_image = nullptr;
        std::array<float,3> drawing_sqare_pos, drawing_sqare_offset;
        std::array<std::array<float,3>,4> square_vertex;
        int aimed_fps;

    public:
        Renderer(int fps);
        ~Renderer();

        void setDrawingTexture(nigf::Image &image);
        void setDrawingSquare(int map_x, int map_y, int draw_x, int draw_y,int draw_z, int draw_w, int draw_h);
        void draw();
        void openGLResize(GLsizei width, GLsizei height);
    };
}