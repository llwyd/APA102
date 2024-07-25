#ifndef SPI_H_
#define SPI_H_

#include <stdbool.h>
#include <stdint.h>

extern bool SPI_Init(const char * const device);
extern void SPI_Write(uint8_t * data, uint8_t len);
extern void SPI_DeInit(void);
#endif /* SPI_H_ */
