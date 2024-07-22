#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "spi.h"

static struct spi_ioc_transfer spi;
int file;

extern bool SPI_Init(const char * const device)
{
    assert(device != NULL);
    bool success = false;
    int ret = 0U;

    /* Attempt to open the SPI device */
    file = open(device, O_RDWR);
    if(file < 0)
    {
        goto cleanup;
    }

    uint8_t mode = SPI_MODE_2 | SPI_NO_CS;
    ret = ioctl(file, SPI_IOC_WR_MODE, &mode);
    if(ret < 0)
    {
        goto cleanup;
    }
    
    ret = ioctl(file, SPI_IOC_RD_MODE, &mode);
    if(ret < 0)
    {
        goto cleanup;
    }

    uint8_t bits_per_word = 0U;
    ret = ioctl(file, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word);
    if(ret < 0)
    {
        goto cleanup;
    }
    
    ret = ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits_per_word);
    if(ret < 0)
    {
        goto cleanup;
    }
    
    uint32_t max_speed = 0x100000;
    
    ret = ioctl(file, SPI_IOC_WR_MAX_SPEED_HZ, &max_speed);
    if(ret < 0)
    {
        goto cleanup;
    }
    
    ret = ioctl(file, SPI_IOC_RD_MAX_SPEED_HZ, &max_speed);
    if(ret < 0)
    {
        goto cleanup;
    }
    
cleanup:
    return success;
}

extern void SPI_Write(uint8_t * data, uint8_t len)
{
    assert(data != NULL);
    assert(len > 0U);

    memset(&spi, 0x00, sizeof(spi));

    spi.tx_buf = (unsigned long)data;
    spi.rx_buf = (unsigned long)NULL;
    spi.len = len;

    if(ioctl(file, SPI_IOC_MESSAGE(1), &spi) < 0)
    {
        /* failed to write */
        assert(false);
    }
}


extern void SPI_DeInit(void)
{
    close(file);
}

