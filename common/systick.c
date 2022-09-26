#include "systick.h"

#define SYSTICK_BASE ( 0xE000E010 )

typedef struct
{
    uint32_t CTRL:32;
    uint32_t LOAD:32;
    uint32_t VAL:32;
    uint32_t CALIB:32;
} systick_t;

_Static_assert( sizeof( systick_t ) == 16, "Systick struct size incorrect" );

static volatile systick_t * const SYSTICK = ( systick_t * ) SYSTICK_BASE;

static uint32_t ms_count;

/* SysTick ISR */
void  __attribute__((interrupt("IRQ"))) _sysTick( void )
{
    ms_count++;
}

extern void SysTick_Init( uint32_t load )
{
    ms_count = 0U;
    
    /* Reset SysTick Counter and COUNTFLAG */
    SYSTICK->VAL = 0x0; 
    SYSTICK->LOAD = load;

    /* Enable SysTick interrupt, counter 
     * and set processor clock as source */
    SYSTICK->CTRL |= 0x7;
}

uint32_t SysTick_GetRaw()
{
    return SYSTICK->VAL; 
}

uint32_t SysTick_GetMS()
{
    return ms_count;
}
