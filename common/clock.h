#ifndef _CLOCK_H_
#define _CLOCK_H_

void Clock_Set8MHz( void );
void Clock_Set48MHz( void );
void Clock_ConfigureGCLK( uint8_t g_clock, uint8_t peripheral );

#endif /* _CLOCK_H_ */
