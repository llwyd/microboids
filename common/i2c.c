
#include "gpio.h"
#include "i2c.h"
#include "clock.h"

#ifdef TARGET_STM32

#define I2C2_BASE ( 0x40005800 )

typedef struct
{
    uint32_t CR1:32;
    uint32_t CR2:32;
    uint32_t OAR1:32;
    uint32_t OAR2:32;
    uint32_t TIMINGR:32;
    uint32_t TIMEOUTR:32;
    uint32_t ISR:32;
    uint32_t ICR:32;
    uint32_t PECR:32;
    uint32_t RXDR:32; 
    uint32_t TXDR:32;
} i2c_t;

static volatile i2c_t  * I2C    = ( i2c_t * )  I2C2_BASE; 
static volatile gpio_t * GPIO   = ( gpio_t * ) GPIOA_BASE;

void I2C_Init( void )
{
    /* Lazy way of enabling gpio a */
    *((uint32_t *)0x40021034) |= ( 0x1 << 0 );

    /* Disable I2C2 */
    I2C->CR1 &= ~0x1;

    /* PA11, PA12, Alt Func 6 (AF6 ) */

    /* Set Alt func */
    GPIO->MODER &= ~( 1 << 22 );
    GPIO->MODER &= ~( 1 << 24 );

    /* Set Open Drain */
    GPIO->OTYPER |= ( 1 << 11 );
    GPIO->OTYPER |= ( 1 << 12 );

    /* Speedy */
    GPIO->OSPEEDR |= ( 0x3 << 22 );
    GPIO->OSPEEDR |= ( 0x3 << 24 );

    /* Alt Func 6 */
    GPIO->AFRH |= ( 0x6 << 12 );
    GPIO->AFRH |= ( 0x6 << 16 );
    
    /* Enable I2C2 Clock */
    *((uint32_t *)0x4002103C) |= ( 0x1 << 22 );

    /* Rise time / Fall Time  */

    /* Turn on peripheral */
    I2C->CR1 |= 0x1;
}

void I2C_Read( uint8_t address, uint8_t * buffer, uint8_t len )
{

}

bool I2C_Write( uint8_t address, uint8_t * buffer, uint8_t len )
{
    bool ret = false;

    /* Tear down previous settings */
    I2C->CR2 = 0x00;
    
    /* 1. Set addressing mode */
    I2C->CR2 |= ( 1 << 25 ); 
    /* 2. Slave address */
    I2C->CR2 |= ( address << 1 );
    /* 3. Transfer Direction */
    I2C->CR2 &= ~( 1 << 10 );
    /* 4. Number of bytes */
    I2C->CR2 |= ( len << 16 );

    /* Send start condition */
    I2C->CR2 |= ( 1 << 13 );

    /* Write data */
    if( !( I2C->ISR & ( 0x1 << 4U ) ) )
    {
        for( unsigned char idx = 0; idx < len; idx++ )
        {
            while( ( I2C->ISR & ( 1 << 1 ) ) != ( 1 << 1 ) );
            I2C->TXDR = buffer[ idx ];
        }
        
        /* Wait for stop condition */
        while( ( I2C->ISR & ( 1 << 5 ) ) != ( 1 << 5 ) );

        /* Clear stop detection flag */
        I2C->ICR |= ( 1 << 5 );

        ret = true;
    }

    return ret;
}

void I2C_WriteCommandByte( const uint8_t address, const uint8_t byte )
{
    /* Tear down previous settings */
    I2C->CR2 = 0x00;
    
    /* 2. Slave address */
    I2C->CR2 |= ( address << 1 );
    /* 3. Transfer Direction */
    I2C->CR2 &= ~( 1 << 10 );
    /* 4. Number of bytes */
    I2C->CR2 |= ( 0x1 << 16 );
    /* set reload */
    I2C->CR2 |= ( 0x1 << 24 );

    /* Send start condition */
    I2C->CR2 |= ( 1 << 13 );
    
    while( ( I2C->ISR & ( 1 << 1 ) ) != ( 1 << 1 ) );
    
    I2C->TXDR = byte;
    while( ( I2C->ISR & ( 1 << 7 ) ) != ( 1 << 7 ) );
}

void I2C_WriteRow( const uint8_t * const byte, uint8_t len )
{
    /* 4. Number of bytes */
    I2C->CR2 &= ~( 0xFF << 16 );
    I2C->CR2 |=  ( len << 16 );
    
    /* set reload */
    I2C->CR2 |= ( 0x1 << 24 );

    for( uint8_t i = 0; i < len; i++ )
    {
        while( ( I2C->ISR & ( 1 << 1 ) ) != ( 1 << 1 ) );
        I2C->TXDR = byte[i];
    }
    while( ( I2C->ISR & ( 1 << 7 ) ) != ( 1 << 7 ) );
}

void I2C_WriteFinalRow( const uint8_t * const byte, uint8_t len )
{
    /* 4. Number of bytes */
    I2C->CR2 |= ( len << 16 );
    /* set reload */
    I2C->CR2 &= ~( 0x1 << 24 );
    I2C->CR2 |= ( 1 << 25 ); 

    for( uint8_t i = 0; i < len; i++ )
    {
        while( ( I2C->ISR & ( 1 << 1 ) ) != ( 1 << 1 ) );
        I2C->TXDR = byte[i];
    } 
    
    /* Wait for stop condition */
    while( ( I2C->ISR & ( 1 << 5 ) ) != ( 1 << 5 ) );

    /* Clear stop detection flag */
    I2C->ICR |= ( 1 << 5 );
}

void I2C_WriteByte( const uint8_t byte )
{ 
}

void I2C_Stop( void )
{ 
}

#elif TARGET_SAMD21

#define GPIO_BASE   ( 0x41004400 )
#define SERCOM_BASE ( 0x42000800 )
#define GCLK_BASE   ( 0x40000C00 )
#define PM_APBC     ( *( ( volatile uint32_t *)0x40000420 ) )

typedef struct
{
    uint32_t CTRLA:32;
    uint32_t CTRLB:32;
    uint32_t RESERVED_0:32;
    uint32_t BAUD:32;
    uint32_t RESERVED_1:32;
    uint8_t INTENCLR:8;
    uint8_t RESERVED_2:8;
    uint8_t INTENSET:8;
    uint8_t RESERVED_3:8;
    uint8_t INTFLAG:8;
    uint8_t RESERVED_4:8;
    uint16_t STATUS:16;
    uint32_t SYNCBUSY:32;
    uint32_t RESERVED_5:32;
    uint32_t ADDR:32;
    uint16_t DATA:16;
    uint8_t RESERVED_6:8;
    uint8_t RESERVED_7:8;
    uint8_t RESERVED_8:8;
    uint8_t RESERVED_9:8;
    uint8_t RESERVED_10:8;
    uint8_t RESERVED_11:8;
    uint8_t DBGCTRL:8;
} i2c_t;

_Static_assert( sizeof( i2c_t ) == 52, "I2C struct size incorrect" );

static volatile i2c_t  * SERCOM    = ( i2c_t * ) SERCOM_BASE; 
static volatile gpio_t * GPIO      = ( gpio_t * ) GPIO_BASE;

void I2C_Init( void )
{
    Clock_ConfigureGCLK( 0x7, 0x1, 0x14 );

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
    SERCOM->BAUD |= ( 23U << 0U );

    SERCOM->CTRLA |= ( 0x1 << 24 );

    /* Enable */
    SERCOM->CTRLA |= ( 0x1 << 1 );
    WAITCLR( SERCOM->SYNCBUSY, 1U);
    
    /* Force IDLE state */
    SERCOM->STATUS |= ( 0x1 << 4 );
    while( ( SERCOM->SYNCBUSY & ( 1 << 2 ) ) );
    
    /* Send ACK after each data read */ 
    SERCOM->CTRLB &= ~( 0x1 << 18 );
}

void I2C_Start( const uint8_t address )
{
    /* Send Address */
    SERCOM->ADDR = ( ( address << 1 ) );
    WAITCLR( SERCOM->SYNCBUSY, 2U );
    WAITSET( SERCOM->INTFLAG, 0U );
}

void I2C_WriteByte( const uint8_t byte )
{
    SERCOM->DATA = byte;
    WAITCLR( SERCOM->SYNCBUSY, 2U );
    WAITSET( SERCOM->INTFLAG, 0U );
}

void I2C_Stop( void )
{
    /* Stop Condition */
    SERCOM->CTRLB |= ( 0x3 << 16 );
    WAITCLR( SERCOM->SYNCBUSY, 2U );
}

extern bool I2C_Write( uint8_t address, uint8_t * buffer, uint8_t len )
{
    bool ret = false;

    /* Send Address */
    SERCOM->ADDR = ( ( address << 1 ) );
    WAITCLR( SERCOM->SYNCBUSY, 2U );
    WAITSET( SERCOM->INTFLAG, 0U );

    if( !(SERCOM->STATUS & ( 0x4 )) )
    {
        /* Write byte and sync */ 
        uint8_t i = 0U;
        for( i = 0U; i < (len - 1U); i++ )
        {
            SERCOM->DATA = buffer[i];
            WAITCLR( SERCOM->SYNCBUSY, 2U );
            WAITSET( SERCOM->INTFLAG, 0U );
        }
    
        SERCOM->DATA = buffer[i];
        WAITCLR( SERCOM->SYNCBUSY, 2U );
        WAITSET( SERCOM->INTFLAG, 0U );
        
        ret = true;
    }

    /* Stop Condition */
    SERCOM->CTRLB |= ( 0x3 << 16 );
    WAITCLR( SERCOM->SYNCBUSY, 2U );
    return ret;
}

extern void I2C_Read( uint8_t address, uint8_t * buffer, uint8_t len )
{
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

#endif

