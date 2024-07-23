#ifndef LED_H_
#define LED_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t r:8;
    uint8_t g:8;
    uint8_t b:8;

    /* Settings */
    uint8_t s:8;
}
led_t;

extern void LED_Init(uint8_t num_leds);

#endif /* LED_H_ */
