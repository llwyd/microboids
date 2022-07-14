#include "display.h"
#include "i2c.h"
#include <stdarg.h>

static void SetupDisplay( int num, ... )
{
    uint8_t commands[4];
    va_list args;

    va_start( args, num );

    for( uint8_t idx = 0U; idx < num; idx++ )
    {
        commands[idx] = (uint8_t)va_arg( args, int );
    }

    va_end( args );

    while( !I2C_Write( 0x3C, commands, num ) );
}

void Display_Init( void )
{
    SetupDisplay( 2U, 0x00, 0xAE );
    SetupDisplay( 3U, 0x00, 0x81, 0x7F );
    SetupDisplay( 3U, 0x00, 0xA8, 63 );
    SetupDisplay( 3U, 0x00, 0xD3, 0x00 );
    SetupDisplay( 2U, 0x00, 0x40 );
    SetupDisplay( 2U, 0x00, 0xa0 | 0x1 );
    SetupDisplay( 3U, 0x00, 0xda, 0x02 | ( 1 << 4 ) | ( 0 << 5 ) );
    SetupDisplay( 2U, 0x00, 0xc0 | ( 1 << 3 ) );
    SetupDisplay( 2U, 0x00, 0xA6 );
    SetupDisplay( 3U, 0x00, 0xD5, ( 15 << 4 | 0x00 ) );
    SetupDisplay( 3U, 0x00, 0x8D, 0x14 );
    SetupDisplay( 2U, 0x00, 0xA4 );
    SetupDisplay( 2U, 0x00, 0xAF );
    SetupDisplay( 3U, 0x00, 0x20, 0 );
    SetupDisplay( 4U, 0x00, 0x21, 0, 127);
    SetupDisplay( 4U, 0x00, 0x22, 0, 7);
}

void Display_Update( const uint8_t frame [ DISPLAY_PAGES ] [ DISPLAY_COLUMNS ] )
{
    uint8_t data[2] = { 0x40, 0x00};

    for( uint8_t i = 0; i < DISPLAY_PAGES; i++ )
    {
        for( uint8_t j = 0; j < DISPLAY_COLUMNS; j++ )
        {
            data[1] = frame[i][j];
            I2C_Write( 0x3C, data, 2U );
        }
    }
}
