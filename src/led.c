#include <assert.h>

#include "led.h"
#include "spi.h"
#include <string.h>

typedef struct
{
    uint8_t r:8;
    uint8_t g:8;
    uint8_t b:8;

    /* Settings */
    uint8_t s:8;
}
led_t;

static led_t * led_array = NULL;
static uint8_t num_leds = 0U;

extern void LED_Init(uint8_t num)
{
    assert(led_array == NULL);
    assert(num > 0U);

    num_leds = num;
    led_array = (led_t *)malloc(num * sizeof(led_t));
    assert(led_array != NULL);
    memset(led_array, 0x00, num * sizeof(led_t));
}

extern void LED_SetColour(uint8_t led, uint8_t r, uint8_t g, uint8_t b)
{
    assert(led < num_leds);
    
    led_array[led].r = r;
    led_array[led].g = g;
    led_array[led].b = b;
}

extern void LED_SetBrightness(uint8_t led, uint8_t b)
{
    led_array[led].s = 0xe0 | b;
}

extern void LED_Refresh(void)
{
}

