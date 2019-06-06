#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

typedef enum
{
    RESOURCE_NONE,
    RESOURCE_LUMBER,
    RESOURCE_BRICK,
    RESOURCE_WOOL,
    RESOURCE_GRAIN,
    RESOURCE_ORE
} Resource;

// An enum element can function as a constant expression for array sizing.
enum
{
    HEX_COUNT = 19
};

static void shuffle(int[], const int);

static void fixNoneIndex(const Resource[HEX_COUNT], int[]);

static void printIsland(const Resource[HEX_COUNT], const int[HEX_COUNT]);

static int getDigit(const int, const int);

int main(void)
{
    srand(time(NULL));

    Resource resources[HEX_COUNT] =
    {
        RESOURCE_NONE,
        RESOURCE_LUMBER,
        RESOURCE_LUMBER,
        RESOURCE_LUMBER,
        RESOURCE_LUMBER,
        RESOURCE_BRICK,
        RESOURCE_BRICK,
        RESOURCE_BRICK,
        RESOURCE_WOOL,
        RESOURCE_WOOL,
        RESOURCE_WOOL,
        RESOURCE_WOOL,
        RESOURCE_GRAIN,
        RESOURCE_GRAIN,
        RESOURCE_GRAIN,
        RESOURCE_GRAIN,
        RESOURCE_ORE,
        RESOURCE_ORE,
        RESOURCE_ORE
    };
    int numbers[HEX_COUNT] =
    {
        2,
        3,
        3,
        4,
        4,
        5,
        5,
        6,
        6,
        8,
        8,
        9,
        9,
        10,
        10,
        11,
        11,
        12,
        0
    };

    shuffle((int*)resources, HEX_COUNT);
    shuffle(numbers, HEX_COUNT - 1);
    fixNoneIndex(resources, numbers);
    printIsland(resources, numbers);

    return 0;
}

static void shuffle(int array[], const int length)
{
    int *const throwArray = malloc(length * sizeof(int));

    for (int index = 0; index < length; index += 1)
    {
        throwArray[index] = array[index];
    }

    for (int index = 0; index < length; index += 1)
    {
        const int randomIndex = rand() % (length - index);
        array[index] = throwArray[randomIndex];
        throwArray[randomIndex] = throwArray[length - index - 1];
    }

    free(throwArray);
}

static void fixNoneIndex(const Resource resources[], int numbers[])
{
    int noneIndex = 0;

    while (resources[noneIndex] != RESOURCE_NONE)
    {
        noneIndex += 1;
    }

    for (int index = noneIndex; index < HEX_COUNT - 1; index += 1)
    {
        const int swappedNumber = numbers[index];
        numbers[index] = numbers[HEX_COUNT - 1];
        numbers[HEX_COUNT - 1] = swappedNumber;
    }
}

static void printIsland(
    const Resource resources[HEX_COUNT],
    const int numbers[HEX_COUNT]
)
{
    // String lengths account for null-terminating character.
    static const char horizontalSpace[5] = "    ";
    static const char verticalSpace[3] = "  ";
    static const char horizontalEdge[5] = "____";

    // Vertical edges stored in top-to-bottom order.
    static const char inclineEdge[2][3] =
    {
        " /",
        "/ "
    };
    static const char declineEdge[2][3] =
    {
        "\\ ",
        " \\"
    };

    // Enum order is assumed to be NONE, LUMBER, BRICK, WOOL, GRAIN, ORE.
    static const char schema[6][3][5] =
    {
        {
            " __ ",
            "|  \\",
            "|__/"
        },
        {
            "    ",
            "|   ",
            "|__ "
        },
        {
            " __ ",
            "|_/ ",
            "|_\\ "
        },
        {
            "    ",
            "/  \\",
            "\\/\\/"
        },
        {
            " __ ",
            "/ _ ",
            "\\__\\"
        },
        {
            " __ ",
            "/  \\",
            "\\__/"
        }
    };

    printf(
        "%s%s%s%s%s%s\n",
        verticalSpace,
        horizontalSpace,
        verticalSpace,
        horizontalSpace,
        verticalSpace,
        horizontalEdge
    );
    printf(
        "%s%s%s%s%s%s%s\n",
        verticalSpace,
        horizontalSpace,
        verticalSpace,
        horizontalSpace,
        inclineEdge[0],
        schema[resources[0]][0],
        declineEdge[0]
    );
    printf(
        "%s%s%s%s%s%s%d%s%s\n",
        verticalSpace,
        horizontalSpace,
        verticalSpace,
        horizontalEdge,
        inclineEdge[1],
        schema[resources[0]][1], 
        getDigit(numbers[0], 2),
        "\\",
        horizontalEdge
    );
    printf(
        "%s%s%s%s%s%s%d%s%s%s\n",
        verticalSpace,
        horizontalSpace,
        inclineEdge[0],
        schema[resources[1]][0],
        declineEdge[0],
        schema[resources[0]][2],
        getDigit(numbers[0], 1),
        "/",
        schema[resources[2]][0],
        declineEdge[0]
    );
    printf(
        "%s%s%s%s%d%s%s%s%s%d%s%s\n",
        verticalSpace,
        horizontalEdge,
        inclineEdge[1],
        schema[resources[1]][1],
        getDigit(numbers[1], 2),
        "\\",
        horizontalEdge,
        inclineEdge[1],
        schema[resources[2]][1],
        getDigit(numbers[2], 2),
        "\\",
        horizontalEdge
    );

    for (int offset = 0; offset < 15; offset += 5)
    {
        const int upperLeftIndex = 1 + offset;
        const int upperLeftResource = resources[upperLeftIndex];
        const int upperLeftNumber = numbers[upperLeftIndex];

        const int upperRightIndex = 2 + offset;
        const int upperRightResource = resources[upperRightIndex];
        const int upperRightNumber = numbers[upperRightIndex];

        const int middleLeftIndex = 3 + offset;
        const Resource middleLeftResource = resources[middleLeftIndex];
        const int middleLeftNumber = numbers[middleLeftIndex];

        const int middleIndex = 4 + offset;
        const int middleResource = resources[middleIndex];
        const int middleNumber = numbers[middleIndex];

        const int middleRightIndex = 5 + offset;
        const int middleRightResource = resources[middleRightIndex];
        const int middleRightNumber = numbers[middleRightIndex];

        const int lowerLeftIndex = 6 + offset;
        const int lowerLeftResource = resources[lowerLeftIndex];
        const int lowerLeftNumber = numbers[lowerLeftIndex];

        const int lowerRightIndex = 7 + offset;
        const int lowerRightResource = resources[lowerRightIndex];
        const int lowerRightNumber = numbers[lowerRightIndex];

        printf(
            "%s%s%s%s%d%s%s%s%s%d%s%s%s\n",
            inclineEdge[0],
            schema[middleLeftResource][0],
            declineEdge[0],
            schema[upperLeftResource][2],
            getDigit(upperLeftNumber, 1),
            "/",
            schema[middleResource][0],
            declineEdge[0],
            schema[upperRightResource][2],
            getDigit(upperRightNumber, 1),
            "/",
            schema[middleRightResource][0],
            declineEdge[0]
        );
        printf(
            "%s%s%d%s%s%s%s%d%s%s%s%s%d%s\n",
            inclineEdge[1],
            schema[middleLeftResource][1],
            getDigit(middleLeftNumber, 2),
            "\\",
            horizontalEdge,
            inclineEdge[1],
            schema[middleResource][1], 
            getDigit(middleNumber, 2),
            "\\",
            horizontalEdge,
            inclineEdge[1],
            schema[middleRightResource][1],
            getDigit(middleRightNumber, 2),
            "\\"
        );
        printf(
            "%s%s%d%s%s%s%s%d%s%s%s%s%d%s\n",
            declineEdge[0],
            schema[middleLeftResource][2],
            getDigit(middleLeftNumber, 1),
            "/",
            schema[lowerLeftResource][0],
            declineEdge[0],
            schema[middleResource][2],
            getDigit(middleNumber, 1),
            "/",
            schema[lowerRightResource][0],
            declineEdge[0],
            schema[middleRightResource][2],
            getDigit(middleRightNumber, 1),
            "/"
        );
        printf(
            "%s%s%s%s%d%s%s%s%s%d%s%s%s\n",
            declineEdge[1],
            horizontalEdge,
            inclineEdge[1],
            schema[lowerLeftResource][1],
            getDigit(lowerLeftNumber, 2),
            "\\",
            horizontalEdge,
            inclineEdge[1],
            schema[lowerRightResource][1],
            getDigit(lowerRightNumber, 2),
            "\\",
            horizontalEdge,
            inclineEdge[1]
        );
    }

    printf(
        "%s%s%s%s%d%s%s%s%s%d%s\n",
        verticalSpace,
        horizontalSpace,
        declineEdge[0],
        schema[resources[16]][2],
        getDigit(numbers[16], 1),
        "/",
        schema[resources[18]][0],
        declineEdge[0],
        schema[resources[17]][2],
        getDigit(numbers[17], 1),
        "/"
    );
    printf(
        "%s%s%s%s%s%s%d%s%s%s\n",
        verticalSpace,
        horizontalSpace,
        declineEdge[1],
        horizontalEdge,
        inclineEdge[1],
        schema[resources[18]][1],
        getDigit(numbers[18], 2),
        "\\",
        horizontalEdge,
        inclineEdge[1]
    );
    printf(
        "%s%s%s%s%s%s%d%s\n",
        verticalSpace,
        horizontalSpace,
        verticalSpace,
        horizontalSpace,
        declineEdge[0],
        schema[resources[18]][2],
        getDigit(numbers[18], 1),
        "/"
    );
    printf(
        "%s%s%s%s%s%s%s\n",
        verticalSpace,
        horizontalSpace,
        verticalSpace,
        horizontalSpace,
        declineEdge[1],
        horizontalEdge,
        inclineEdge[1]
    );
}

static int getDigit(const int number, const int place)
{
    return (number / (int)pow(10, place - 1)) % 10;
}
