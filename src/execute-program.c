#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "execute-program.h"

static void checkShader(const GLuint shaderIdentifier)
{
    GLint logLength = 0;
    glGetShaderiv(shaderIdentifier, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0)
    {
        GLchar *const message = malloc(logLength * sizeof(GLchar));
        glGetShaderInfoLog(shaderIdentifier, logLength, NULL, message);
        printf("%s\n", message);
        free(message);
    }
}

static void loadShader(const GLuint shaderIdentifier, const char contents[])
{
    glShaderSource(shaderIdentifier, 1, &contents, NULL);
    checkShader(shaderIdentifier);
}

static void loadContents(const GLuint shaderIdentifier, FILE *const file)
{
    fseeko(file, 0, SEEK_END);
    const off_t fileSize = ftello(file);
    fseeko(file, 0, SEEK_SET);
    char *const contents = malloc(fileSize * sizeof(char) + 1);
    fread(contents, sizeof(char), fileSize, file);
    contents[fileSize] = '\0';
    loadShader(shaderIdentifier, contents);
    free(contents);
}

static void loadFile(const GLuint shaderIdentifier, const char path[])
{
    FILE *const file = fopen(path, "r");
    loadContents(shaderIdentifier, file);
    fclose(file);
}

static void loadPath(const GLuint shaderIdentifier, const char filename[])
{
    static const char pathToAssets[] = "./assets/";
    char *const pathToFile = malloc(
        strlen(pathToAssets) + strlen(filename) + 1
    );
    strcpy(pathToFile, pathToAssets);
    strcat(pathToFile, filename);
    loadFile(shaderIdentifier, pathToFile);
    free(pathToFile);
}

static void checkProgram(const GLuint programIdentifier)
{
    GLint logLength = 0;
    glGetProgramiv(programIdentifier, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0)
    {
        GLchar *const message = malloc(logLength * sizeof(GLchar));
        glGetProgramInfoLog(programIdentifier, logLength, NULL, message);
        printf("%s\n", message);
        free(message);
    }
}

typedef void (*Execute)(GLFWwindow *const, GLuint);

static void compileProgram(
    GLFWwindow *const window,
    const Execute execute,
    const GLuint vertexShaderIdentifier,
    const GLuint fragmentShaderIdentifier
)
{
    const GLuint programIdentifier = glCreateProgram();
    glAttachShader(programIdentifier, vertexShaderIdentifier);
    glAttachShader(programIdentifier, fragmentShaderIdentifier);
    glLinkProgram(programIdentifier);
    glDetachShader(programIdentifier, fragmentShaderIdentifier);
    glDetachShader(programIdentifier, vertexShaderIdentifier);
    checkProgram(programIdentifier);
    execute(window, programIdentifier);
    glDeleteProgram(programIdentifier);
}

static void compileFragmentShader(
    GLFWwindow *const window,
    const Execute execute,
    const GLuint vertexShaderIdentifier
)
{
    const GLuint fragmentShaderIdentifier = glCreateShader(GL_FRAGMENT_SHADER);
    loadPath(fragmentShaderIdentifier, "shader.frag");
    glCompileShader(fragmentShaderIdentifier);
    compileProgram(
        window,
        execute,
        vertexShaderIdentifier,
        fragmentShaderIdentifier
    );
    glDeleteShader(fragmentShaderIdentifier);
}

static void compileVertexShader(GLFWwindow *const window, const Execute execute)
{
    const GLuint vertexShaderIdentifier = glCreateShader(GL_VERTEX_SHADER);
    loadPath(vertexShaderIdentifier, "shader.vert");
    glCompileShader(vertexShaderIdentifier);
    compileFragmentShader(window, execute, vertexShaderIdentifier);
    glDeleteShader(vertexShaderIdentifier);
}

void executeProgram(GLFWwindow *const window, const Execute execute)
{
    compileVertexShader(window, execute);
}
