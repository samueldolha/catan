#include <stddef.h>
#include <stdlib.h>

#include "generate-island.h"
#include "hex-count.h"
#include "polygon-count.h"
#include "token-count.h"

typedef enum
{
    HEX_FOREST = 0,
    HEX_HILLS = 1,
    HEX_PASTURE = 2,
    HEX_FIELD = 3,
    HEX_MOUNTAIN = 4,
    HEX_DESERT = 5
} Hex;

typedef enum
{
    TOKEN_TWO = 6,
    TOKEN_THREE = 7,
    TOKEN_FOUR = 8,
    TOKEN_FIVE = 9,
    TOKEN_SIX = 10,
    TOKEN_EIGHT = 11,
    TOKEN_NINE = 12,
    TOKEN_TEN = 13,
    TOKEN_ELEVEN = 14,
    TOKEN_TWELVE = 15,
} Token;

static void shuffleArray(int array[], const int length)
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

size_t generateIsland(const Texture textures[], Texture island[])
{
    Hex hexes[hexCount] =
    {
        HEX_FOREST,
        HEX_FOREST,
        HEX_FOREST,
        HEX_FOREST,
        HEX_HILLS,
        HEX_HILLS,
        HEX_HILLS,
        HEX_PASTURE,
        HEX_PASTURE,
        HEX_PASTURE,
        HEX_PASTURE,
        HEX_FIELD,
        HEX_FIELD,
        HEX_FIELD,
        HEX_FIELD,
        HEX_MOUNTAIN,
        HEX_MOUNTAIN,
        HEX_MOUNTAIN,
        HEX_DESERT
    };

    shuffleArray((int*)hexes, hexCount);

    size_t indexOfDesertHex = 0;

    for (size_t index = 0; index < hexCount; index += 1)
    {
        const Hex hex = hexes[index];

        if (hex == HEX_DESERT)
        {
            indexOfDesertHex = index;
        }

        island[index] = textures[hex];
    }

    Token tokens[tokenCount] =
    {
        TOKEN_TWO,
        TOKEN_THREE,
        TOKEN_THREE,
        TOKEN_FOUR,
        TOKEN_FOUR,
        TOKEN_FIVE,
        TOKEN_FIVE,
        TOKEN_SIX,
        TOKEN_SIX,
        TOKEN_EIGHT,
        TOKEN_EIGHT,
        TOKEN_NINE,
        TOKEN_NINE,
        TOKEN_TEN,
        TOKEN_TEN,
        TOKEN_ELEVEN,
        TOKEN_ELEVEN,
        TOKEN_TWELVE
    };

    shuffleArray((int*)tokens, tokenCount);

    for (size_t index = hexCount; index < polygonCount; index += 1)
    {
        island[index] = textures[tokens[index - hexCount]];
    }

    return indexOfDesertHex;
}
