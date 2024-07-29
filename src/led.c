#include <assert.h>

#include "led.h"
#include "spi.h"
#include <string.h>

#define SPI_BUFFER_SIZE (4U)

typedef struct
{
    rgb_t rgb;
    /* Settings */
    uint8_t s:8;
}
led_t;

static led_t * led_array = NULL;
static uint8_t num_leds = 0U;

extern void LED_Init(const char * const device, uint8_t num)
{
    assert(led_array == NULL);
    assert(num > 0U);

    num_leds = num;
    led_array = (led_t *)malloc(num * sizeof(led_t));
    assert(led_array != NULL);
    memset(led_array, 0x00, num * sizeof(led_t));

    SPI_Init(device);
}

extern void LED_SetColour(uint8_t led, const rgb_t * const rgb)
{
    assert(led < num_leds);
    
    led_array[led].rgb.r = rgb->r;
    led_array[led].rgb.g = rgb->g;
    led_array[led].rgb.b = rgb->b;
}

extern void LED_SetAll(const rgb_t * const rgb, uint8_t s)
{
    for(uint8_t idx = 0U; idx < num_leds; idx++)
    {
        led_array[idx].rgb.r = rgb->r;
        led_array[idx].rgb.g = rgb->g;
        led_array[idx].rgb.b = rgb->b;

        LED_SetBrightness(idx, s);
    }
}

extern void LED_SetBrightness(uint8_t led, uint8_t b)
{
    led_array[led].s = 0xe0 | b;
}

extern void LED_Refresh(void)
{
    uint8_t buffer[SPI_BUFFER_SIZE];

    /* Send Start */
    memset(buffer, 0x00, SPI_BUFFER_SIZE);
    SPI_Write(buffer, SPI_BUFFER_SIZE);
   
    for(uint8_t idx = 0U; idx < num_leds; idx++)
    {
        buffer[0] = led_array[idx].s;
        buffer[1] = led_array[idx].rgb.b;
        buffer[2] = led_array[idx].rgb.g;
        buffer[3] = led_array[idx].rgb.r;
        SPI_Write(buffer, SPI_BUFFER_SIZE);
    }

    /* Send End */
    memset(buffer, 0xFF, SPI_BUFFER_SIZE);
    SPI_Write(buffer, SPI_BUFFER_SIZE);
}

extern void LED_Close(void)
{
    free(led_array);
    SPI_DeInit();
}

