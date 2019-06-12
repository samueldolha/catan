#include <stddef.h>
#include <stdlib.h>

#include "generate-island.h"
#include "generate-vertex-arrays.h"
#include "load-textures.h"
#include "polygon.h"
#include "polygon-count.h"
#include "hex-count.h"
#include "hex-index-count.h"
#include "hex-vertex-count.h"
#include "render-program.h"
#include "texture.h"
#include "texture-count.h"
#include "token-index-count.h"
#include "token-indices.h"
#include "token-vertex-count.h"

static void renderIsland(
    GLFWwindow *const window,
    const GLuint programIdentifier,
    const Polygon polygons[]
)
{
    const GLint textureSampler = glGetUniformLocation(
        programIdentifier,
        "textureSampler"
    );

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programIdentifier);

        for (size_t index = 0; index < polygonCount; index += 1)
        {
            const Polygon polygon = polygons[index];
            glActiveTexture(GL_TEXTURE0 + polygon.texture.unitIndex);
            glBindTexture(GL_TEXTURE_2D, polygon.texture.identifier);
            glUniform1i(textureSampler, polygon.texture.unitIndex);
            glBindVertexArray(polygon.objects.vertexArrayIdentifier);
            glDrawElements(
                GL_TRIANGLES,
                (sizeof(Vertex) / sizeof(GLfloat)) * polygon.vertices.count,
                GL_UNSIGNED_INT,
                0
            );
            glBindVertexArray(0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

static void renderPolygons(
    GLFWwindow *const window,
    const GLuint programIdentifier,
    const Polygon polygons[]
)
{
    static const GLuint vertexPositionIndex = 0;
    static const GLuint texturePositionIndex = 1;

    for (size_t index = 0; index < polygonCount; index += 1)
    {
        const Polygon polygon = polygons[index];
        glBindVertexArray(polygon.objects.vertexArrayIdentifier);
        glBindBuffer(GL_ARRAY_BUFFER, polygon.objects.vertexBufferIdentifier);
        glBufferData(
            GL_ARRAY_BUFFER,
            polygon.vertices.count * sizeof(Vertex),
            polygon.vertices.data,
            GL_STATIC_DRAW
        );
        glBindBuffer(
            GL_ELEMENT_ARRAY_BUFFER, polygon.objects.indexBufferIdentifier
        );
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            polygon.indices.count * sizeof(TriangleIndex),
            polygon.indices.data,
            GL_STATIC_DRAW
        );
        glEnableVertexAttribArray(vertexPositionIndex);
        glVertexAttribPointer(
            vertexPositionIndex,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (GLvoid *const)0
        );
        glEnableVertexAttribArray(texturePositionIndex);
        glVertexAttribPointer(
            texturePositionIndex,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (GLvoid *const)offsetof(Vertex, texturePosition)
        );
    }

    renderIsland(window, programIdentifier, polygons);

    glDisableVertexAttribArray(texturePositionIndex);
    glDisableVertexAttribArray(vertexPositionIndex);
}

void renderProgram(GLFWwindow *const window, const GLuint programIdentifier)
{
    GLuint *const vertexArrayIdentifiers = calloc(polygonCount, sizeof(GLuint));
    GLuint *const vertexBufferIdentifiers = calloc(
        polygonCount,
        sizeof(GLuint)
    );
    GLuint *const indexBufferIdentifiers = calloc(polygonCount, sizeof(GLuint));
    glGenVertexArrays(polygonCount, vertexArrayIdentifiers);
    glGenBuffers(polygonCount, vertexBufferIdentifiers);
    glGenBuffers(polygonCount, indexBufferIdentifiers);

    GLuint *const textureIdentifiers = calloc(textureCount, sizeof(GLuint));
    glGenTextures(textureCount, textureIdentifiers);
    Texture *textures = calloc(textureCount, sizeof(Texture));
    loadTextures(textures, textureIdentifiers);

    Texture *const island = calloc(polygonCount, sizeof(Texture));
    const size_t indexOfDesertHex = generateIsland(textures, island);

    Vertex **const vertexArrays = calloc(
        polygonCount,
        sizeof(Vertex*)
    );

    for (size_t index = 0; index < polygonCount; index += 1)
    {
        vertexArrays[index] = calloc(
            (index < hexCount) ? hexVertexCount : tokenVertexCount,
            sizeof(Vertex)
        );
    }

    generateVertexArrays(vertexArrays, indexOfDesertHex);

    Polygon *const polygons = calloc(polygonCount, sizeof(Polygon));

    for (size_t index = 0; index < polygonCount; index += 1)
    {
        polygons[index].objects.vertexArrayIdentifier =
            vertexArrayIdentifiers[index];
        polygons[index].objects.vertexBufferIdentifier =
            vertexBufferIdentifiers[index];
        polygons[index].objects.indexBufferIdentifier =
            indexBufferIdentifiers[index];

        polygons[index].vertices.data = vertexArrays[index];
        polygons[index].vertices.count =
            (index < hexCount) ? hexVertexCount : tokenVertexCount;

        if (index < hexCount)
        {
            static const TriangleIndex hexIndices[hexIndexCount] =
            {
                { 0, 1, 2 },
                { 0, 2, 3 },
                { 1, 2, 5 },
                { 1, 4, 5 },
                { 2, 3, 5 },
                { 3, 5, 6 },
                { 4, 5, 7 },
                { 5, 6, 7 }
            };
            polygons[index].indices.data = hexIndices;
            polygons[index].indices.count = hexIndexCount;
        }
        else
        {
            polygons[index].indices.data = tokenIndices;
            polygons[index].indices.count = tokenIndexCount;
        }

        polygons[index].texture = island[index];
    }

    renderPolygons(window, programIdentifier, polygons);

    free(polygons);

    free(island);

    glDeleteTextures(textureCount, textureIdentifiers);

    for (size_t index = 0; index < polygonCount; index += 1)
    {
        free(vertexArrays[index]);
    }

    free(vertexArrays);

    glDeleteVertexArrays(polygonCount, vertexArrayIdentifiers);
    free(vertexArrayIdentifiers);
    glDeleteBuffers(polygonCount, vertexBufferIdentifiers);
    free(vertexBufferIdentifiers);
    glDeleteBuffers(polygonCount, indexBufferIdentifiers);
    free(indexBufferIdentifiers);
}
