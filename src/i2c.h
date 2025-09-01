#ifndef _I2C_H_
#define _I2C_H_

#include "util.h"
extern void I2C_Init( void );
extern void I2C_Read( uint8_t address, uint8_t * buffer, uint8_t len );
extern bool I2C_Write( uint8_t address, uint8_t * buffer, uint8_t len );

void I2C_WriteRow( const uint8_t * const byte, uint8_t len );
void I2C_WriteFinalRow( const uint8_t * const byte, uint8_t len );
void I2C_WriteCommandByte( const uint8_t address, const uint8_t byte );

void I2C_Start( const uint8_t address );
void I2C_WriteByte( const uint8_t byte );
void I2C_Stop( void );

#endif /* _I2C_H_ */
