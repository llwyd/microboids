#ifndef __UTIL_H_
#define __UTIL_H_

typedef enum {false, true} bool;

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;


#define SET(X, Y, Z) ( (X) |=  ( (Y) << (Z) ) )
#define CLR(X, Y, Z) ( (X) &= ~( (Y) << (Z) ) )
#define TOG(X, Y, Z) ( (X) ^=  ( (Y) << (Z) ) )

#define WAITSET( X, Y ) while( !( (X) & ( 1U << (Y) ) ) )
#define WAITCLR( X, Y ) while(  ( (X) & ( 1U << (Y) ) ) )

typedef struct
{
    bool pin0:1;
    bool pin1:1;
    bool pin2:1;
    bool pin3:1;
    bool pin4:1;
    bool pin5:1;
    bool pin6:1;
    bool pin7:1;
    bool pin8:1;
    bool pin9:1;
    bool pin10:1;
    bool pin11:1;
    bool pin12:1;
    bool pin13:1;
    bool pin14:1;
    bool pin15:1;
    bool pin16:1;
    bool pin17:1;
    bool pin18:1;
    bool pin19:1;
    bool pin20:1;
    bool pin21:1;
    bool pin22:1;
    bool pin23:1;
    bool pin24:1;
    bool pin25:1;
    bool pin26:1;
    bool pin27:1;
    bool pin28:1;
    bool pin29:1;
    bool pin30:1;
    bool pin31:1;
} reg_bit_t;

typedef struct
{
    unsigned char nib0:4;
    unsigned char nib1:4;
    unsigned char nib2:4;
    unsigned char nib3:4;
    unsigned char nib4:4;
    unsigned char nib5:4;
    unsigned char nib6:4;
    unsigned char nib7:4;
} reg_nib_t;

typedef struct
{
    unsigned char byte0:8;
    unsigned char byte1:8;
    unsigned char byte2:8;
    unsigned char byte3:8;
} reg_byte_t;

typedef struct
{
    unsigned char CTRL:8;
    unsigned char STATUS:8;
    unsigned short CLKCTRL:16;
    unsigned int GENCTRL:32;
    unsigned int GENDEV:32;
} gclk_t;

#endif /* __UTIL_H_ */
