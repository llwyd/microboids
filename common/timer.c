#include "timer.h"
#include "clock.h"

#ifdef TARGET_STM32

static volatile timer_t * TIM2 = ( timer_t * ) TIM2_BASE;

#define TIM2_SECOND_COUNT ( 0x3D09 )

extern void Timer_Init( void )
{
    /* Enable TIM2 */
    *((uint32_t *)0x4002103C) |= ( 0x1 << 0U );
    
    /* Enable NVIC */
    NVIC_ISER |= ( 1 << 15U );

    /* 64MHz Source clock, prescalar of 4095 for 15kHzish*/
    TIM2->PSC = 4095;

    /* 1s Pulse */
    TIM2->ARR = ( TIM2_SECOND_COUNT >> 4 );

    /* Enable Interrupts */
    TIM2->DIER |= ( 0x1 << 0U );
}

extern void Timer_Start( void )
{
    TIM2->CR1 |= ( 0x1 << 0U );
}

extern void Timer_ClearInterrupt( void )
{
    NVIC_ICPR |= ( 0x1 << 15U );
    TIM2->SR &= ~( 0x1 << 0U );
}

/*
void Timer_UpdatePeriod( void )
{

}
*/
#elif TARGET_SAMD21

#define PM_APBC     ( *( ( volatile unsigned int *)0x40000420 ) )

/* 64 prescaler, 1MHz / 64 = 15625 */
#define TCC0_SECOND_COUNT ( 0x3D09 )
#define TCC0_DEFAULT_COUNT ( TCC0_SECOND_COUNT << 1U )

static volatile timer_t * TCC0 = ( timer_t * ) TCC0_BASE;

void Timer_Init( void )
{
    /* 1Mhz clock source, TCC0 */
    Clock_ConfigureGCLK( 0x6, 0x5, 0x1A );

    PM_APBC |= ( 0x1 << 8U );

    TCC0->CTRLA |= ( 0x5 << 8 );
    TCC0->CC0 = ( TCC0_DEFAULT_COUNT );

    /* MFRQ Mode */
    TCC0->WAVE |= ( 0x1 << 0U );

    TCC0->CTRLA |= ( 0x1 << 12 ) | ( 0x1 << 11 );
    TCC0->INTENSET |= ( 0x1 << 16 );
}

void Timer_Start( void )
{
    TCC0->CTRLA |= ( 0x1 << 1 );
}

void Timer_ClearInterrupt( void )
{
    TCC0->INTFLAG |= ( 0x1 << 16 );
}

void Timer_UpdatePeriod( uint8_t shift )
{
    TCC0->CC0 = ( ( TCC0_DEFAULT_COUNT ) >> shift );
    TCC0->CTRLBSET = ( 0x1 << 5U );
}

#endif
