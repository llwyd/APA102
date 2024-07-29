#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "led.h"
#include "spi.h"
#include <unistd.h>

typedef struct
{
    rgb_t rgb;
    uint8_t brightness;
    uint8_t num_leds;
}
settings_t;

static uint8_t ParseNumberU8(const char * const arg)
{
    uint8_t value = 0U;
    
    uint32_t raw = (uint32_t)atoi(arg);
    
    if(raw > UINT8_MAX)
    {
        value = UINT8_MAX;
    }
    else
    {
        value = (uint8_t)raw;
    }

    return value;
}

static bool ParseArgs(int argc, char ** argv, settings_t * settings)
{
    int input_flags;
    bool num_leds_set = false;
    memset(settings, 0x00, sizeof(settings_t));
    
    while( ( input_flags = getopt( argc, argv, "r:g:b:s:n:" ) ) != -1 )
    {
        switch( input_flags )
        {
            case 'n':
            {
                settings->num_leds = ParseNumberU8(optarg); 
                num_leds_set = true;
                break;
            }
            case 'r':
            {
                settings->rgb.r = ParseNumberU8(optarg); 
                break;
            }
            case 'g':
            {
                settings->rgb.g = ParseNumberU8(optarg); 
                break;
            }
            case 'b':
            {
                settings->rgb.b = ParseNumberU8(optarg); 
                break;
            }
            case 's':
            {
                settings->brightness = ParseNumberU8(optarg); 
                break;
            }
            default:
                break;
        }
    }

    return num_leds_set;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    settings_t settings;
    bool num_leds_set = ParseArgs(argc, argv, &settings);

    if(num_leds_set)
    {
        printf(" num leds: %u\n", settings.num_leds);
        printf("intensity: %u\n", settings.brightness);
        printf("        r: 0x%x\n", settings.rgb.r);
        printf("        g: 0x%x\n", settings.rgb.g);
        printf("        b: 0x%x\n", settings.rgb.b);
    }
    else
    {
        printf("Number of LEDs not set\n");
    }
    /*
    LED_Init("/dev/spidev0.0", 8U);
    LED_SetAll(0xFF,0x00,0x00,0xFF);
    LED_Refresh();
    LED_Refresh();
    LED_Close();
    */
    return 0U;
}
