#include "renderer.hpp"
#include <GL/freeglut.h>

#include <iostream>

nie::Renderer::Renderer(int fps)
    : aimed_fps(fps)
{
}

nie::Renderer::~Renderer()
{
}

void nie::Renderer::setDrawingTexture(nigf::Image &image)
{
    drawing_image = &image;
}

void nie::Renderer::setDrawingSquare(int map_x, int map_y, int draw_x, int draw_y, int draw_z, int draw_w, int draw_h)
{
    drawing_sqare_pos[0] = static_cast<float>(draw_x) / static_cast<float>(map_x);
    drawing_sqare_pos[1] = static_cast<float>(draw_y) / static_cast<float>(map_y);
    drawing_sqare_pos[2] = static_cast<float>(draw_z / 100);

    drawing_sqare_offset[0] = static_cast<float>(draw_w) / static_cast<float>(map_x);
    drawing_sqare_offset[1] = static_cast<float>(draw_h) / static_cast<float>(map_y);
    drawing_sqare_offset[2] = static_cast<float>(draw_z / 100);

    square_vertex[0] = {drawing_sqare_pos[0], drawing_sqare_pos[1], drawing_sqare_pos[2]};
    square_vertex[1] = {drawing_sqare_pos[0] + drawing_sqare_offset[0], drawing_sqare_pos[1], drawing_sqare_pos[2]};
    square_vertex[3] = {drawing_sqare_pos[0], drawing_sqare_pos[1] - drawing_sqare_offset[1], drawing_sqare_pos[2]};
    square_vertex[2] = {drawing_sqare_pos[0] + drawing_sqare_offset[0], drawing_sqare_pos[1] - drawing_sqare_offset[1], drawing_sqare_pos[2]};
}

void nie::Renderer::swap()
{
    glutSwapBuffers();
}

void nie::Renderer::openGLResize(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
}

void nie::Renderer::draw()
{
    if (!drawing_image)
        return;
    // glBindTexture(GL_TEXTURE_2D,*(drawing_image->get_data()));
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);                            //支持4字节对齐
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);      // S方向上贴图
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);      // T方向上贴图
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //放大纹理过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //缩小纹理过滤方式

    glTexImage2D(GL_TEXTURE_2D, 0, 3, drawing_image->get_width(), drawing_image->get_hight(), 0, GL_RGB, GL_UNSIGNED_BYTE, drawing_image->get_data()); //载入纹理：

    glMatrixMode(GL_MODELVIEW);  // 选择模型观察矩阵
    glLoadIdentity();            // 重置模型观察矩阵
    glMatrixMode(GL_PROJECTION); // 选择投影矩阵
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D); //启用2D纹理映射
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(square_vertex[0][0], square_vertex[0][1], square_vertex[0][2]);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(square_vertex[1][0], square_vertex[1][1], square_vertex[1][2]);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(square_vertex[2][0], square_vertex[2][1], square_vertex[2][2]);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(square_vertex[3][0], square_vertex[3][1], square_vertex[3][2]);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glFlush();
}

void nie::Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}