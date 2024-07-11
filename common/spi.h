#ifndef _SPI_H_
#define _SPI_H_

#include "util.h"

#if defined TARGET_SAMD21
#include "clock.h"
extern void SPI_Init( void );
extern void SPI_Write( void );
extern void SPI_WriteMSB( uint8_t * data, uint8_t len );

#else

#include <stdint.h>
#include <stdbool.h>
extern void SPI_Init( void );
extern void SPI_WriteByte(uint8_t data);
#endif

#endif /* _SPI_H_ */
