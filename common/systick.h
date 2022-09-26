#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "util.h"

void SysTick_Init( uint32_t load );

uint32_t SysTick_GetRaw();
uint32_t SysTick_GetMS();

#endif /* _SYSTICK_H_ */
