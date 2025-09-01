#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "util.h"

extern void SysTick_Init( uint32_t load );
extern uint32_t SysTick_GetRaw();
extern uint32_t SysTick_GetMS();
extern void SysTick_Delay(uint32_t delay_ms);

#endif /* _SYSTICK_H_ */
