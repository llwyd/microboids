#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define DISPLAY_COLUMNS ( 128U )
#define DISPLAY_ROWS    ( 8U )
#define DISPLAY_PAGES   ( 8U )
#define DISPLAY_FULL_ROWS   ( DISPLAY_ROWS * DISPLAY_PAGES )

void Display_Init( void );
void Display_Update( const uint8_t frame [ DISPLAY_PAGES ] [ DISPLAY_COLUMNS ] ); 

#endif /* DISPLAY_H */
