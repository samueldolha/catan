#include "execute-program.h"
#include "render-window.h"

void renderWindow(const int width, const int height, const char title[])
{
    GLFWwindow *const window = glfwCreateWindow(
        width,
        height,
        title,
        NULL,
        NULL
    );

    if (window != NULL)
    {
        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;
        glewInit();
        glfwSwapInterval(1);

        executeProgram(window);

        glfwDestroyWindow(window);
    }
}
