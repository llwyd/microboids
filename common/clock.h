#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <stdint.h>

#ifdef TARGET_STM32

void Clock_Set64MHz( void );

#elif TARGET_SAMD21
void Clock_Set8MHz( void );
void Clock_Set48MHz( void );
void Clock_ConfigureGCLK( uint8_t source, uint8_t g_clock, uint8_t peripheral );
void Clock_Divide( uint8_t g_clock, uint8_t div );

#else
_Static_assert(false, "No target defined in clock.h");
#endif

#endif /* _CLOCK_H_ */
