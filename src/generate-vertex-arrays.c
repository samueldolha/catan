#include "generate-vertex-arrays.h"
#include "polygon-count.h"
#include "vertex-count.h"

void generateVertexArrays(Vertex *const vertexArrays[])
{
    for (
        size_t polygonIndex = 0;
        polygonIndex < polygonCount;
        polygonIndex += 1
    )
    {
        Vertex *const vertices = vertexArrays[polygonIndex];

        for (
            size_t vertexIndex = 0;
            vertexIndex < vertexCount;
            vertexIndex += 1
        )
        {
            static const TwoDimensionalVector vertexPositions[vertexCount] =
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
            static const TwoDimensionalVector offsets[polygonCount] =
            {
                { -2.0,  3.0 },
                {  0.0,  3.0 },
                {  2.0,  3.0 },
                { -3.0,  1.5 },
                { -1.0,  1.5 },
                {  1.0,  1.5 },
                {  3.0,  1.5 },
                { -4.0,  0.0 },
                { -2.0,  0.0 },
                {  0.0,  0.0 },
                {  2.0,  0.0 },
                {  4.0,  0.0 },
                { -3.0, -1.5 },
                { -1.0, -1.5 },
                {  1.0, -1.5 },
                {  3.0, -1.5 },
                { -2.0, -3.0 },
                {  0.0, -3.0 },
                {  2.0, -3.0 }
            };
            static const TwoDimensionalVector texturePositions[vertexCount] =
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

            vertices[vertexIndex].vertexPosition.x = 0.2
                * (vertexPositions[vertexIndex].x + offsets[polygonIndex].x);
            vertices[vertexIndex].vertexPosition.y = 0.25
                * (vertexPositions[vertexIndex].y + offsets[polygonIndex].y);
            vertices[vertexIndex].texturePosition =
                texturePositions[vertexIndex];
        }
    }
}
