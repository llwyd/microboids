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

static void ConfigurePins( void )
{
    /* Reset PA0/1 */
    GPIO->DIRR |= ( 0x3 );
    GPIO->OUTSET |= ( 0x3 );
    
    /* PA0 = MOSI, MUX D */
    GPIO->PINCFG0 |= 0x1;
    GPIO->PMUX0 |= 0x3;

    /* PA1 = SCK, MUX D */
    GPIO->PINCFG1 |= 0x1;
    GPIO->PMUX0 |= ( 0x3 << 4U );
}

static void ConfigurePeripheral( void )
{
    /* SERCOM1 */

    /* Host Mode */
    SERCOM->CTRLA |= ( 0x3 << 2U );

    /* High when idle */
    SERCOM->CTRLA |= ( 0x1 << 29U );

    /* Falling, change, Rising, Sample */
    SERCOM->CTRLA |= ( 0x1 << 28U );

    /* leave frame format as-is */

    /* Data in pinout as PAD3, though this isn't used */
    SERCOM->CTRLA |= ( 0x3 << 20U );

    /* Data out as pad0, SCK as PAD 1, no change needed */

    /* Character Size, 8bit, no change needed */

    /* Data Order Bit, no change needed */

    /* Baud rate, 1Mhz */
    SERCOM->BAUD |= 0x3;

    /* Enable */
    SERCOM->CTRLA |= ( 0x1 << 1U );

}

extern void SPI_Init( void )
{
    Clock_ConfigureGCLK( 0x2, 0x15 );

    /* Enable SERCOM1 */
    PM_APBC |= ( 0x1 << 3U );

    ConfigurePins();
    ConfigurePeripheral();
}

extern void SPI_Write( void )
{
    uint8_t data[12] = {    0x00, 0x00, 0x00, 0x00,
                            0xe1, 0x00, 0xff, 0x00,
                            0xff,0xff,0xff,0xff };

    for( int idx = 0; idx < 12; idx++ )
    {
        SERCOM->DATA = data[idx];
        WAITSET( SERCOM->INTFLAG, 0U);
    }
}

extern void SPI_WriteMSB( uint8_t * data, uint8_t len )
{
    uint8_t num_elements = len >> 2U;
    for( int idx = 0; idx < num_elements; idx++ )
    {
        int actual_index = ( 4 * ( idx + 1 ) ) - 1U;
        for( int jdx = 0; jdx < 4; jdx++ )
        {
            SERCOM->DATA = data[actual_index--];
            WAITSET( SERCOM->INTFLAG, 0U);
        } 
    }
}

