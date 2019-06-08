#include <stdlib.h>

#include "render-program.h"
#include "render-window.h"
#include "run-application.h"

static void run(void)
{
    renderWindow(640, 480, "Catan Island Generator", renderProgram);
}

int main(void)
{
    runApplication(run);

    return EXIT_SUCCESS;
}
