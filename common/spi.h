#ifndef _SPI_H_
#define _SPI_H_

#include "util.h"
#include "clock.h"

extern void SPI_Init( void );
extern void SPI_Write( void );
extern void SPI_WriteMSB( uint8_t * data, uint8_t len );

#endif /* _SPI_H_ */
