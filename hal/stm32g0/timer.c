#include "timer.h"

#define TIM2_BASE ( 0x40000000 )

typedef struct
{
    uint32_t CR1:32;
    uint32_t CR2:32;
    uint32_t SMCR:32;
    uint32_t DIER:32;
    uint32_t SR:32;
    uint32_t EGR:32;
    uint32_t CCMR1:32;
    uint32_t CCMR2:32;
    uint32_t CCER:32;
    uint32_t CNT:32;
    uint32_t PSC:32;
    uint32_t ARR:32;
    uint32_t CCR1:32;
    uint32_t CCR2:32;
    uint32_t CCR3:32;
    uint32_t CCR4:32;
    uint32_t RESERVED0:32;
    uint32_t DCR:32;
    uint32_t DMAR:32;
    uint32_t TIM2_OR1:32;
    uint32_t TIM3_OR1:32;
    uint32_t TIM4_OR1:32;
    uint32_t TIM2_AF1:32;
    uint32_t TIM3_AF1:32;
    uint32_t TIM4_AF1:32;
    uint32_t TIM2_TISEL:32;
    uint32_t TIM3_TISEL:32;
    uint32_t TIM4_TISEL:32;
}
timer_t;

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
