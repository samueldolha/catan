#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "render-window.h"
#include "run-application.h"

static void handleError(const int code, const char *const description)
{
    fprintf(stderr, "Error %d: %s\n", code, description);
}

static void initializeVersion()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void runApplication(void)
{
    glfwSetErrorCallback(handleError);

    if (glfwInit())
    {
        initializeVersion();
        renderWindow();
        glfwTerminate();
    }
}
