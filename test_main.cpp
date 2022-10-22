#include <iostream>
#include <image.hpp>
#include <gameplay.hpp>
#include <GL/freeglut.h>

nigf::Image image("../resource/error.jpg");
GLuint texture = 0;

constexpr int32_t WORLD_SIZE_X = 512;
constexpr int32_t WORLD_SIZE_Y = 512;

int32_t gameobject_pos_x = 0;
int32_t gameobject_pos_y = 0;
int32_t gameobject_pos_z = 0;
uint32_t gameobject_size_w = 50;
uint32_t gameobject_size_h = 50;
int32_t gameobject_size_z = 1;

int32_t gameobject_speed_x = 0;
int32_t gameobject_speed_y = 0;

static void drawPoints()
{
    glBegin(GL_POINTS);
    glVertex2f(0.1f, 0.2f);
    glVertex2f(0.0f, 0.0f);
    glEnd();
}

static void drawTexture()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);                            //支持4字节对齐
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);      // S方向上贴图
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);      // T方向上贴图
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //放大纹理过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //缩小纹理过滤方式

    glTexImage2D(GL_TEXTURE_2D, 0, 3, image.getWidth(), image.getHight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.getData()); //载入纹理：

    glMatrixMode(GL_MODELVIEW);  // 选择模型观察矩阵
    glLoadIdentity();            // 重置模型观察矩阵
    glMatrixMode(GL_PROJECTION); // 选择投影矩阵
    glLoadIdentity();

    float pos[3];
    pos[0] = static_cast<float>(gameobject_pos_x) / static_cast<float>(WORLD_SIZE_X);
    pos[1] = static_cast<float>(gameobject_pos_y) / static_cast<float>(WORLD_SIZE_Y);
    pos[2] = static_cast<float>(gameobject_pos_z);

    float len[3];
    len[0] = static_cast<float>(gameobject_size_w) / static_cast<float>(WORLD_SIZE_X);
    len[1] = static_cast<float>(gameobject_size_h) / static_cast<float>(WORLD_SIZE_Y);
    len[2] = static_cast<float>(gameobject_size_z);

    float square[4][3] = {{pos[0], pos[1], pos[2]}, {pos[0] + len[0], pos[1], pos[2]}, {pos[0], pos[1] - len[1], pos[2]}, {pos[0] + len[0], pos[1] - len[1], pos[2]}};

    glEnable(GL_TEXTURE_2D); //启用2D纹理映射
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(square[0][0], square[0][1], square[0][2]);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(square[1][0], square[1][1], square[1][2]);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(square[3][0], square[3][1], square[3][2]);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(square[2][0], square[2][1], square[2][2]);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawPoints();
    drawTexture();
    glFlush();
    glutSwapBuffers();
}

static GLvoid reSizeGLScene(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
}

// why unsigned char...
static void keyboardDown(unsigned char input, int mouseX, int mouseY)
{
    switch (input)
    {
    case 'w':
        gameobject_speed_y = 1;
        break;
    case 's':
        gameobject_speed_y = -1;
        break;
    case 'a':
        gameobject_speed_x = -1;
        break;
    case 'd':
        gameobject_speed_x = 1;
        break;

    default:
        break;
    }
}

static void keyboardUp(unsigned char input, int mouseX, int mouseY)
{
    switch (input)
    {
    case 'w':
        gameobject_speed_y = 0;
        break;
    case 's':
        gameobject_speed_y = 0;
        break;
    case 'a':
        gameobject_speed_x = 0;
        break;
    case 'd':
        gameobject_speed_x = 0;
        break;

    default:
        break;
    }
}

void onFream(int id)
{
    gameobject_pos_x += gameobject_speed_x;
    gameobject_pos_y += gameobject_speed_y;

    display();
    glutTimerFunc(16, onFream, id);
}

int main(int argc, char *argv[]) noexcept
{
    std::cout << "hello world\n";

    image.resize(512, 512);
    texture = *image.getData();

    nigf::Gameplay gp("hello world!", 800, 600, 60, &argc, argv);
    gp.bind_ondraw(display);
    gp.bind_onresize(reSizeGLScene);
    gp.bind_onkeyboard_down(keyboardDown);
    gp.bind_onkeyboard_up(keyboardUp);
    gp.bind_ontick(onFream);

    if(!gp.main_loop())
    {
        std::cerr << "Gameplay error: " << gp.get_error_msg() << '\n';
        return -1;
    }

    return 0;
}