#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "three-dimensional-vector.h"
#include "two-dimensional-vector.h"

typedef struct
{
    ThreeDimensionalVector vertexPosition;
    TwoDimensionalVector texturePosition;
} Vertex;
