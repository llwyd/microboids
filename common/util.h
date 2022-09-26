#ifndef __UTIL_H_
#define __UTIL_H_

#include <stdint.h>
#include <stdbool.h>

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
    uint32_t IPRO0:32;
    uint32_t IPRO1:32;
    uint32_t IPRO2:32;
    uint32_t IPRO3:32;
    uint32_t IPRO4:32;
    uint32_t IPRO5:32;
    uint32_t IPRO6:32;
    uint32_t IPRO7:32;
} nvic_ipro_t;

#define NVIC_ISER ( *( ( volatile unsigned int *)0xE000E100 ) )
#define NVIC_ICER ( *( ( volatile unsigned int *)0xE000E180 ) )
#define NVIC_ISPR ( *( ( volatile unsigned int *)0xE000E200 ) )
#define NVIC_ICPR ( *( ( volatile unsigned int *)0xE000E280 ) )
#define NVIC_IPRO ( *( ( volatile unsigned int *)0xE000E400 ) )

#endif /* __UTIL_H_ */
