
#include "util.h"
#include "clock.h"

/* NVM */
#define NVM_CTRL       ( *( ( volatile unsigned int *)0x41004004 ) )
#define NVM_CALIB       ( *( ( volatile unsigned int *)0x00806024 ) )

#define DFL_CTRL        ( *( ( volatile unsigned int *)0x40000824 ) )
#define DFL_VAL         ( *( ( volatile unsigned int *)0x40000828 ) )

#define GCLK_BASE   ( 0x40000C00 )
volatile gclk_t * GCLKK      = ( gclk_t * ) GCLK_BASE;

void Clock_Set8MHz( void )
{

}

void Clock_Set48MHz( void )
{
    /* Higher clock requires a wait state */
    NVM_CTRL |= ( 0x1 << 1 ); 

    /* Get coarse calibration value from NVM */
    unsigned int calib = NVM_CALIB;
    calib = ( calib >> 26 );
    calib &= 0x3F;

    /* Configure 48MHz reference in open loop */
    CLR( DFL_CTRL, 1, 7 );
    DFL_VAL |= ( calib << 10U ); 
    DFL_CTRL |= ( 1 << 1U );

    /* Configure GCLK 0 to use 48MHz as main clock */ 
    unsigned int val = ( 1 << 16U ) | ( 0x7 << 8U );
    GCLKK->GENCTRL = val;

    WAITCLR( GCLKK->STATUS, 7 );
}
