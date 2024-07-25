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


#ifdef __arm__
static struct spi_ioc_transfer spi;
int fd;

static bool Configure(int * fd, unsigned long op, uint8_t data)
{
    bool success = true; 
    int err = ioctl(*fd, op, &data);
    
    if(err < 0)
    {
        success = false;
    }

    return success;
}

static bool Configure32(int * fd, unsigned long op, uint32_t data)
{
    bool success = true; 
    int err = ioctl(*fd, op, &data);
    
    if(err < 0)
    {
        success = false;
    }

    return success;
}
#endif

extern bool SPI_Init(const char * const device)
{
    assert(device != NULL);
    bool success = false;
#ifdef __arm__

    /* Attempt to open the SPI device */
    fd = open(device, O_RDWR);
    if(fd < 0)
    {
        goto cleanup;
    }

    if(!Configure(&fd, SPI_IOC_WR_MODE, SPI_MODE_2 | SPI_NO_CS))
    {
        goto cleanup;
    }

    /* 0 signifies 0 bits per word */
    if(!Configure(&fd, SPI_IOC_WR_BITS_PER_WORD, 0U))
    {
        goto cleanup;
    }
    
    if(!Configure(&fd, SPI_IOC_WR_LSB_FIRST, 0U))
    {
        goto cleanup;
    }

    if(!Configure32(&fd, SPI_IOC_WR_MAX_SPEED_HZ, 0x100000))
    {
        goto cleanup;
    }    

cleanup:
#endif
    return success;
}

extern void SPI_Write(uint8_t * data, uint8_t len)
{
    assert(data != NULL);
    assert(len > 0U);

#ifdef __arm__
    memset(&spi, 0x00, sizeof(spi));

    spi.tx_buf = (unsigned long)data;
    spi.len = len;

    if(ioctl(fd, SPI_IOC_MESSAGE(1), &spi) < 0)
    {
        /* failed to write */
        assert(false);
    }
#endif
}


extern void SPI_DeInit(void)
{
#ifdef __arm__
    close(fd);
#endif
}

