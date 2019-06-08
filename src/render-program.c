#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render-program.h"

static void updateViewport(GLFWwindow *const window)
{
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

void renderProgram(
    GLFWwindow *const window,
    const GLuint programIdentifier
)
{
    static const GLfloat vertices[] =
    {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f
    };

    GLuint vertexArrayIdentifier = 0;
    glGenVertexArrays(1, &vertexArrayIdentifier);
    glBindVertexArray(vertexArrayIdentifier);

    GLuint vertexBufferIdentifier = 0;
    glGenBuffers(1, &vertexBufferIdentifier);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferIdentifier);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window))
    {
        updateViewport(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programIdentifier);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferIdentifier);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertexBufferIdentifier);

    glDeleteVertexArrays(1, &vertexArrayIdentifier);
}
