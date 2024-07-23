#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "spi.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    SPI_Init(NULL);
    SPI_DeInit();
    return 0U;
}
