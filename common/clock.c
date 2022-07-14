
#include "util.h"
#include "clock.h"

/* NVM */
#define NVM_CTRL       ( *( ( volatile uint32_t *)0x41004004 ) )
#define NVM_CALIB       ( *( ( volatile uint32_t *)0x00806024 ) )

#define DFL_CTRL        ( *( ( volatile uint32_t *)0x40000824 ) )
#define DFL_VAL         ( *( ( volatile uint32_t *)0x40000828 ) )

#define GCLK_BASE   ( 0x40000C00 )

typedef struct
{
    uint8_t CTRL:8;
    uint8_t STATUS:8;
    uint16_t CLKCTRL:16;
    uint32_t GENCTRL:32;
    uint32_t GENDIV:32;
} gclk_t;

_Static_assert( sizeof( gclk_t ) == 12U , "GCLK struct size incorrect" );

volatile gclk_t * GCLKK      = ( gclk_t * ) GCLK_BASE;

void Clock_Set8MHz( void )
{

}

void Clock_Set48MHz( void )
{
    /* Higher clock requires a wait state */
    NVM_CTRL |= ( 0x1 << 1 ); 

    /* Get coarse calibration value from NVM */
    uint32_t calib = NVM_CALIB;
    calib = ( calib >> 26 );
    calib &= 0x3F;

    /* Configure 48MHz reference in open loop */
    CLR( DFL_CTRL, 1, 7 );
    DFL_VAL |= ( calib << 10U ); 
    DFL_CTRL |= ( 1 << 1U );

    /* Configure GCLK 0 to use 48MHz as main clock */ 
    uint32_t val = ( 1 << 16U ) | ( 0x7 << 8U );
    GCLKK->GENCTRL = val;

    WAITCLR( GCLKK->STATUS, 7 );
}

void Clock_ConfigureGCLK( uint8_t source, uint8_t g_clock, uint8_t peripheral )
{
    /* Configure GCLK */
    uint32_t val = 0U;
    val = ( 1 << 16 ) | ( source << 0x8 ) | g_clock;
    GCLKK->GENCTRL = val;
    WAITCLR( GCLKK->STATUS, 7U );

    /* Set GCLK_x as clock for peripheral */
    uint16_t short_val = ( 1 << 14 ) | ( g_clock << 8 ) | ( peripheral << 0 );
    GCLKK->CLKCTRL = short_val;
    WAITCLR( GCLKK->STATUS, 7U );
}

void Clock_Divide( uint8_t g_clock, uint8_t div )
{
    uint32_t val = 0U;
    val = ( div << 8U ) | g_clock;
    GCLKK->GENDIV |= val;
    WAITCLR( GCLKK->STATUS, 7U );
}

