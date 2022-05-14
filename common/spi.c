#include "spi.h"

#define GPIO_BASE       ( 0x41004400 )
#define GCLK_BASE       ( 0x40000C00 )
#define SERCOM1_BASE    ( 0x42000C00 )
#define PM_APBC     ( *( ( volatile unsigned int *)0x40000420 ) )

typedef struct
{
    unsigned int CTRLA:32;
    unsigned int CTRLB:32;
    unsigned int RESERVED_0:32;
    unsigned int BAUD:8;
    unsigned int RESERVED_1:8;
    unsigned int RESERVED_2:16;
    unsigned int RESERVED_3:32; 
    unsigned char INTENCLR:8;
    unsigned char RESERVED_4:8;
    unsigned char INTENSET:8;
    unsigned char RESERVED_5:8;
    unsigned char INTFLAG:8;
    unsigned char RESERVED_6:8;
    unsigned short STATUS:16;
    unsigned int SYNCBUSY:32;
    unsigned int RESERVED_7:32;
    unsigned int ADDR:32;
    unsigned short DATA:16;
    unsigned char RESERVED_8:8;
    unsigned char RESERVED_9:8;
    unsigned char RESERVED_10:8;
    unsigned char RESERVED_11:8;
    unsigned char RESERVED_12:8;
    unsigned char RESERVED_13:8;
    unsigned char DBGCTRL:8;
} spi_t;

volatile spi_t  * SERCOM    = ( spi_t * )  SERCOM1_BASE; 
volatile gpio_t * GPIO      = ( gpio_t * ) GPIO_BASE;
volatile gclk_t * GCLK      = ( gclk_t * ) GCLK_BASE;

extern void SPI_Init( void )
{

}

