#include <math.h>
#include <GLFW/glfw3.h>
#define TICKRATE 1
#define PI 3.141592653f

using namespace std;

class RotatingTriangle
{
    double x;
    double y;

    double size;
    double rotation_speed;

    double age = 0;

    double rotation = PI/2;

    public:
        RotatingTriangle(float x, float y, float size, float rotSpeed)
        {
            this->x = x;
            this->y = y;

            this->size = size;
            this->rotation_speed = rotSpeed;

            this->age = 0;
        }

    int update()
    {
        this->age += TICKRATE;

        this->rotation += TICKRATE * this->rotation_speed;

        double top_x = cos(this->rotation);
        double top_y = sin(this->rotation);

        double left_x = cos(this->rotation + (2 * PI / 3));
        double left_y = sin(this->rotation + (2 * PI / 3));

        double right_x = cos(this->rotation - (2 * PI / 3));
        double right_y = sin(this->rotation - (2 * PI / 3));

        glBegin(GL_TRIANGLES);
        glVertex2d(left_x * this->size, left_y * this->size);
        glVertex2d(top_x * this->size, top_y * this->size);
        glVertex2d(right_x * this->size, right_y * this->size);
        glEnd();

        return 0;
    }
};

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    RotatingTriangle currentTriangle = RotatingTriangle(0,0,0.25,0.0001);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        currentTriangle.update();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}