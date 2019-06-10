#include <stddef.h>
#include <stdlib.h>

#include "generate-island.h"
#include "polygon-count.h"

typedef enum
{
    FOREST = 0,
    HILLS = 1,
    PASTURE = 2,
    FIELD = 3,
    MOUNTAIN = 4,
    DESERT = 5
} Hex;

static void shuffleArray(Hex array[], const int length)
{
    int *const temporaryArray = malloc(length * sizeof(int));

    for (int index = 0; index < length; index += 1)
    {
        temporaryArray[index] = array[index];
    }

    for (int index = 0; index < length; index += 1)
    {
        const int randomIndex = rand() % (length - index);
        array[index] = temporaryArray[randomIndex];
        temporaryArray[randomIndex] = temporaryArray[length - index - 1];
    }

    free(temporaryArray);
}

void generateIsland(const Texture textures[], Texture island[])
{
    Hex hexes[polygonCount] =
    {
        FOREST,
        FOREST,
        FOREST,
        FOREST,
        HILLS,
        HILLS,
        HILLS,
        PASTURE,
        PASTURE,
        PASTURE,
        PASTURE,
        FIELD,
        FIELD,
        FIELD,
        FIELD,
        MOUNTAIN,
        MOUNTAIN,
        MOUNTAIN,
        DESERT,
    };

    shuffleArray(hexes, polygonCount);

    for (size_t index = 0; index < polygonCount; index += 1)
    {
        island[index] = textures[hexes[index]];
    }
}
