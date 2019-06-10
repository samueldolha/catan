#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "triangle-index.h"
#include "vertex.h"

typedef struct
{
    struct
    {
        GLuint vertexArrayIdentifier;
        GLuint vertexBufferIdentifier;
        GLuint indexBufferIdentifier;
    } objects;
    struct
    {
        const Vertex *data;
        size_t count;
    } vertices;
    struct
    {
        const TriangleIndex *data;
        size_t count;
    } indices;
    Texture texture;
} Polygon;

