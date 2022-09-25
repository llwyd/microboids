#ifndef TIMER_H
#define TIMER_H

#include "util.h"

void Timer_Init( void );
void Timer_Start( void );
void Timer_ClearInterrupt( void );

#ifdef TARGET_STM32

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

#elif TARGET_SAMD21

typedef struct
{
    uint32_t CTRLA:32;
    uint8_t CTRLBCLR:8;
    uint8_t CTRLBSET:8;
    uint8_t _RESERVED_0:8;
    uint8_t _RESERVED_1:8;
    uint32_t SYNCBUSY:32;
    uint32_t FCTRLA:32;
    uint32_t FCTRLB:32;
    uint32_t WEXCTRL:32;
    uint32_t DRVCTRL:32;
    uint8_t _RESERVED_2:8;
    uint8_t _RESERVED_3:8;
    uint8_t DBGCTRL:8;
    uint8_t _RESERVED_4:8;
    uint32_t EVCTRL:32;
    uint32_t INTENCLR:32;
    uint32_t INTENSET:32;
    uint32_t INTFLAG:32;
    uint32_t STATUS:32;
    uint32_t COUNT:32;
    uint16_t PATT:16;
    uint8_t _RESERVED_5:8;
    uint8_t _RESERVED_6:8;
    uint32_t WAVE:32;
    uint32_t PER:32;
    uint32_t CC0:32;
    uint32_t CC1:32;
    uint32_t CC2:32;
    uint32_t CC3:32;
    uint32_t _RESERVED_7:32;
    uint32_t _RESERVED_8:32;
    uint32_t _RESERVED_9:32;
    uint8_t _RESERVED_10:8;
    uint8_t _RESERVED_11:8;
    uint8_t _RESERVED_12:8;
    uint16_t PATTB:16;
    uint8_t _RESERVED_13:8;
    uint8_t _RESERVED_14:8;
    uint32_t WAVEB:32;
    uint32_t PERB:32;
    uint32_t CCB0:32;
    uint32_t CCB1:32;
    uint32_t CCB2:32;
    uint32_t CCB3:32;
}
timer_t;

#define TCC0_BASE ( 0x42002000 )
#define TCC1_BASE ( 0x42002400 )
#define TCC2_BASE ( 0x42002800 )

void Timer_UpdatePeriod( uint8_t shift );

#endif

#endif /* TIMER_H */
