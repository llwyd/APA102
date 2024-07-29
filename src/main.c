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
    char * device;
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
    bool device_set = false;
    memset(settings, 0x00, sizeof(settings_t));
    
    while( ( input_flags = getopt( argc, argv, "r:g:b:s:n:d:" ) ) != -1 )
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
            case 'd':
            {
                settings->device = optarg;
                device_set = true;
            }
            default:
                break;
        }
    }

    return (num_leds_set && device_set);
}

int main(int argc, char **argv)
{
    settings_t settings;
    bool parameters_set = ParseArgs(argc, argv, &settings);

    if(parameters_set)
    {
        printf("   device: %s\n", settings.device);
        printf(" num leds: %u\n", settings.num_leds);
        printf("intensity: %u\n", settings.brightness);
        printf("        r: 0x%x\n", settings.rgb.r);
        printf("        g: 0x%x\n", settings.rgb.g);
        printf("        b: 0x%x\n", settings.rgb.b);
    
        LED_Init(settings.device, settings.num_leds);
        LED_SetAll(settings.rgb.r, settings.rgb.g, settings.rgb.b, settings.brightness);
        LED_Refresh();
        LED_Refresh();
        LED_Close();
    }
    else
    {
        printf("Number of LEDs or DEVICE not set\n");
    }
    
    return 0U;
}
