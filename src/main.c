#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "led.h"
#include "spi.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    LED_Init("/dev/spidev0.0", 8U);
    LED_SetAll(0xFF,0x00,0x00,0xFF);
    LED_Refresh();
    LED_Refresh();
    LED_Close();
    return 0U;
}
