#include "i2c.h"

#define GPIO_BASE   ( 0x41004400 )
#define SERCOM_BASE ( 0x42000800 )
#define GCLK_BASE   ( 0x40000C00 )
#define PM_APBC     ( *( ( volatile unsigned int *)0x40000420 ) )

typedef struct
{
    unsigned int CTRLA:32;
    unsigned int CTRLB:32;
    unsigned int RESERVED_0:32;
    unsigned int BAUD:32;
    unsigned int RESERVED_1:32;
    unsigned char INTENCLR:8;
    unsigned char RESERVED_2:8;
    unsigned char INTENSET:8;
    unsigned char RESERVED_3:8;
    unsigned char INTFLAG:8;
    unsigned char RESERVED_4:8;
    unsigned short STATUS:16;
    unsigned int SYNCBUSY:32;
    unsigned int RESERVED_5:32;
    unsigned int ADDR:32;
    unsigned short DATA:16;
    unsigned char RESERVED_6:8;
    unsigned char RESERVED_7:8;
    unsigned char RESERVED_8:8;
    unsigned char RESERVED_9:8;
    unsigned char RESERVED_10:8;
    unsigned char RESERVED_11:8;
    unsigned char DBGCTRL:8;
} i2c_t;

typedef struct
{
    unsigned char CTRL:8;
    unsigned char STATUS:8;
    unsigned short CLKCTRL:16;
    unsigned int GENCTRL:32;
    unsigned int GENDEV:32;
} gclk_t;

typedef struct
{
    unsigned int DIRR:32;
    unsigned int DIRCLR:32;
    unsigned int DIRSET:32;
    unsigned int DIRTGL:32;
    unsigned int OUT:32;
    unsigned int OUTCLR:32;
    unsigned int OUTSET:32;
    unsigned int OUTTGL:32;
    unsigned int IN:32;
    unsigned int CTRL:32;
    unsigned int WRCONFIG:32;
    unsigned int RESERVED_0:32;
    unsigned char PMUX0:8;
    unsigned char PMUX1:8;
    unsigned char PMUX2:8;
    unsigned char PMUX3:8;
    unsigned char PMUX4:8;
    unsigned char PMUX5:8;
    unsigned char PMUX6:8;
    unsigned char PMUX7:8;
    unsigned char PMUX8:8;
    unsigned char PMUX9:8;
    unsigned char PMUX10:8;
    unsigned char PMUX11:8;
    unsigned char PMUX12:8;
    unsigned char PMUX13:8;
    unsigned char PMUX14:8;
    unsigned char PMUX15:8;
    unsigned char PINCFG0:8;
    unsigned char PINCFG1:8;
    unsigned char PINCFG2:8;
    unsigned char PINCFG3:8;
    unsigned char PINCFG4:8;
    unsigned char PINCFG5:8;
    unsigned char PINCFG6:8;
    unsigned char PINCFG7:8;
    unsigned char PINCFG8:8;
    unsigned char PINCFG9:8;
    unsigned char PINCFG10:8;
    unsigned char PINCFG11:8;
    unsigned char PINCFG12:8;
    unsigned char PINCFG13:8;
    unsigned char PINCFG14:8;
    unsigned char PINCFG15:8;
    unsigned char PINCFG16:8;
    unsigned char PINCFG17:8;
    unsigned char PINCFG18:8;
    unsigned char PINCFG19:8;
    unsigned char PINCFG20:8;
    unsigned char PINCFG21:8;
    unsigned char PINCFG22:8;
    unsigned char PINCFG23:8;
    unsigned char PINCFG24:8;
    unsigned char PINCFG25:8;
    unsigned char PINCFG26:8;
    unsigned char PINCFG27:8;
    unsigned char PINCFG28:8;
    unsigned char PINCFG29:8;
    unsigned char PINCFG30:8;
    unsigned char PINCFG31:8;
} gpio_t;


volatile i2c_t  * SERCOM    = ( i2c_t * ) SERCOM_BASE; 
volatile gpio_t * GPIO      = ( gpio_t * ) GPIO_BASE;
volatile gclk_t * GCLK      = ( gclk_t * ) GCLK_BASE;

void I2C_Init( void )
{
    /* GCLK */
    /* Set main clk as source for gclk1 */
    unsigned int val = 0U;
    val = ( 1 << 16 ) | ( 1 << 0x6 ) | ( 1 << 0 );
    GCLK->GENCTRL |= val;
    WAITCLR( GCLK->STATUS, 7U );

    /* Set GCLK1 as clock for SERCOM0 */
    unsigned short short_val = ( 1 << 14 ) | ( 1 << 8 ) | ( 0x14 << 0 );
    GCLK->CLKCTRL |= short_val;
    WAITCLR( GCLK->STATUS, 7U );

    PM_APBC |= ( 0x1 << 2U );

    /* GPIO */
    /* PA8 = SDA, MUX C */
    GPIO->DIRR |= ( 0x3 << 8 );
    GPIO->OUTSET |= ( 0x3 << 8 );
    GPIO->PINCFG8 |= ( 0x1 << 0 );
    GPIO->PMUX4 |= 0x2;
    
    /* PA9 = SCL, MUX C */
    GPIO->PINCFG9 |= ( 0x1 << 0 );
    GPIO->PMUX4 |= ( 0x2 << 4 );

    /* SERCOM 0 */
    /* Set I2C Host Mode */
    SERCOM->CTRLA |= ( 0x5 << 2U );

    /* Enable Smart mode */
    SERCOM->CTRLB |= ( 0x1 << 8U );

    /* Enable SCL Timeout */
    SERCOM->CTRLA |= ( 0x1 << 30U ) | ( 0x1 << 22 );

    /* Baud */
    SERCOM->BAUD |= ( 0x4 << 0U );

    /* Enable */
    SERCOM->CTRLA |= ( 0x1 << 1 );
    WAITCLR( SERCOM->SYNCBUSY, 1U);

}

extern void I2C_Read( uint8_t address, uint8_t * buffer, uint8_t len )
{
    /* Force IDLE state */
    SERCOM->STATUS |= ( 0x1 << 4 );
    while( ( SERCOM->SYNCBUSY & ( 1 << 2 ) ) );
   
    /* Send ACK after each data read */ 
    SERCOM->CTRLB &= ~( 0x1 << 18 );

    /* Send Address */
    SERCOM->ADDR = ( ( address << 1 ) | 0x1);
    while( ( SERCOM->SYNCBUSY & ( 1 << 2 ) ) );
    while( !( SERCOM->INTFLAG & ( 1 << 1 ) ) );
   
    /* Read byte and sync */ 
    uint8_t i = 0U;
    for( i = 0U; i < (len - 1U); i++ )
    {
        buffer[i] = SERCOM->DATA;
        WAITCLR( SERCOM->SYNCBUSY, 2U );
        WAITSET( SERCOM->INTFLAG, 1U );
    }

    /* Read Last Byte */
    buffer[i] = SERCOM->DATA;
    WAITCLR( SERCOM->SYNCBUSY, 2U );
    WAITCLR( SERCOM->INTFLAG, 1 );
  
    /* Stop Condition */
    SERCOM->CTRLB |= ( 0x3 << 16 );
    WAITCLR( SERCOM->SYNCBUSY, 2U );
}



