#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "run-application.h"

int main(void)
{
    srand(time(NULL));

    runApplication();

    return EXIT_SUCCESS;
}
