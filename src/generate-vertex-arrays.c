#include <math.h>
#include <stddef.h>

#include "generate-vertex-arrays.h"
#include "hex-count.h"
#include "hex-vertex-count.h"
#include "polygon-count.h"
#include "token-index-count.h"
#include "token-vertex-count.h"

static float convertComponent(const float component)
{
    return (component + 1) / 2;
}

void generateVertexArrays(
    Vertex *const vertexArrays[],
    const size_t indexOfDesertHex
)
{
    static const TwoDimensionalVector hexOffsets[hexCount] =
    {
        { -0.4,  0.75 },
        {  0.0,  0.75 },
        {  0.4,  0.75 },
        { -0.6,  0.375 },
        { -0.2,  0.375 },
        {  0.2,  0.375 },
        {  0.6,  0.375 },
        { -0.8,  0.0 },
        { -0.4,  0.0 },
        {  0.0,  0.0 },
        {  0.4,  0.0 },
        {  0.8,  0.0 },
        { -0.6, -0.375 },
        { -0.2, -0.375 },
        {  0.2, -0.375 },
        {  0.6, -0.375 },
        { -0.4, -0.75 },
        {  0.0, -0.75 },
        {  0.4, -0.75 }
    };

    static const float hexXFactor = 0.2;
    static const float hexYFactor = 0.25;

    for (size_t hexIndex = 0; hexIndex < hexCount; hexIndex += 1)
    {
        Vertex *const vertices = vertexArrays[hexIndex];

        for (
            size_t vertexIndex = 0;
            vertexIndex < hexVertexCount;
            vertexIndex += 1
        )
        {
            static const TwoDimensionalVector vertexPositions[hexVertexCount] =
            {
                {  0.0,  1.0 },
                { -1.0,  0.5 },
                {  0.0,  0.5 },
                {  1.0,  0.5 },
                { -1.0, -0.5 },
                {  0.0, -0.5 },
                {  1.0, -0.5 },
                {  0.0, -1.0 }
            };
            static const TwoDimensionalVector texturePositions[hexVertexCount] =
            {
                { 0.5, 1.0 },
                { 0.0, 0.75 },
                { 0.5, 0.75 },
                { 1.0, 0.75 },
                { 0.0, 0.25 },
                { 0.5, 0.25 },
                { 1.0, 0.25 },
                { 0.5, 0.0 }
            };

            vertices[vertexIndex].vertexPosition.x =
                (hexXFactor * vertexPositions[vertexIndex].x)
                + hexOffsets[hexIndex].x;
            vertices[vertexIndex].vertexPosition.y =
                (hexYFactor * vertexPositions[vertexIndex].y)
                + hexOffsets[hexIndex].y;
            vertices[vertexIndex].texturePosition =
                texturePositions[vertexIndex];
        }
    }

    size_t tokenIndexOffset = 0;

    for (
        size_t tokenIndex = hexCount;
        tokenIndex < polygonCount;
        tokenIndex += 1
    )
    {
        if (tokenIndex - hexCount == indexOfDesertHex)
        {
            tokenIndexOffset = 1;
        }

        const size_t adjustedTokenIndex = tokenIndex + tokenIndexOffset;
        const float centerX = hexOffsets[adjustedTokenIndex - hexCount].x;
        const float centerY = hexOffsets[adjustedTokenIndex - hexCount].y;

        Vertex *const vertices = vertexArrays[tokenIndex];
        vertices[0].vertexPosition.x = centerX;
        vertices[0].vertexPosition.y = centerY;
        vertices[0].texturePosition.x = convertComponent(0);
        vertices[0].texturePosition.y = convertComponent(0);

        const float theta = (2 * 3.14159265358979323846) / tokenIndexCount;
        const float cosTheta = cosf(theta);
        const float sinTheta = sinf(theta);

        float t = 1;
        float x = 1;
        float y = 0;

        for (
            size_t vertexIndex = 1;
            vertexIndex < tokenVertexCount;
            vertexIndex += 1
        )
        {
            const float tokenFactor = 397.0 / 1233.0 * hexXFactor;
            vertices[vertexIndex].vertexPosition.x =
                (tokenFactor * x) + centerX;
            vertices[vertexIndex].vertexPosition.y =
                (tokenFactor * y) + centerY;
            vertices[vertexIndex].texturePosition.x = convertComponent(x);
            vertices[vertexIndex].texturePosition.y = convertComponent(y);
            t = x;
            x = (cosTheta * x) - (sinTheta * y);
            y = (sinTheta * t) + (cosTheta * y);
        }
    }
}
