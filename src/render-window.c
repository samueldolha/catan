#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "load-program.h"
#include "render-window.h"

static void handleKeyEvent(
    GLFWwindow *const window,
    const int key,
    const int scancode,
    const int action,
    const int modifiers
)
{
    if (key == GLFW_KEY_ESCAPE
        && scancode != 0
        && action == GLFW_PRESS
        && modifiers == 0
    )
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void renderWindow(void)
{
    GLFWmonitor *const monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *const videoMode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

    GLFWwindow *const window = glfwCreateWindow(
        videoMode->width,
        videoMode->height,
        "Catan Island Generator",
        monitor,
        NULL
    );

    if (window != NULL)
    {
        glfwSetKeyCallback(window, handleKeyEvent);
        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;
        glewInit();

        loadProgram(window);

        glfwDestroyWindow(window);
    }
}
