#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "run-application.h"

static void handleError(const int code, const char *const description)
{
    fprintf(stderr, "Error %d: %s\n", code, description);
}

void runApplication(void (*const run)(void))
{
    glfwSetErrorCallback(handleError);

    if (glfwInit())
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        run();
        glfwTerminate();
    }
}
