#include "i2c.h"

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

void I2C_Init( void )
{
    /* Lazy way of enabling gpio a */
    *((uint32_t *)0x40021034) |= ( 0x1 << 0 );

    /* Disable I2C2 */
    I2C->CR1 &= ~0x1;
    
    /* Enable I2C2 Clock */
    *((uint32_t *)0x4002103C) |= ( 0x1 << 22 );

    /* Rise time / Fall Time from CUBEMX tool.  Super fast mode  */
    I2C->TIMINGR |= 0x300B29;

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
