#ifndef _I2C_H_
#define _I2C_H_

#include "util.h"
extern void I2C_Init( void );
extern void I2C_Read( uint8_t address, uint8_t * buffer, uint8_t len );
extern bool I2C_Write( uint8_t address, uint8_t * buffer, uint8_t len );

#endif /* _I2C_H_ */
