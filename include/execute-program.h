#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef void (*Execute)(GLFWwindow *const, GLuint);

void executeProgram(GLFWwindow *const, const Execute);
