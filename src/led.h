#ifndef LED_H_
#define LED_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

extern void LED_Init(uint8_t num_leds);
extern void LED_SetColour(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
extern void LED_SetAll(uint8_t r, uint8_t g, uint8_t b, uint8_t s);
extern void LED_SetBrightness(uint8_t led, uint8_t b);
extern void LED_Refresh(void);

#endif /* LED_H_ */
