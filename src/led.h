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
}
rgb_t;

extern void LED_Init(const char * const device, uint8_t num);
extern void LED_SetColour(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
extern void LED_SetAll(uint8_t r, uint8_t g, uint8_t b, uint8_t s);
extern void LED_SetBrightness(uint8_t led, uint8_t b);
extern void LED_Refresh(void);
extern void LED_Close(void);

#endif /* LED_H_ */
