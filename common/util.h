#ifndef __UTIL_H_
#define __UTIL_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define SET(X, Y, Z) ( (X) |=  ( (Y) << (Z) ) )
#define CLR(X, Y, Z) ( (X) &= ~( (Y) << (Z) ) )
#define TOG(X, Y, Z) ( (X) ^=  ( (Y) << (Z) ) )

#define WAITSET( X, Y ) while( !( (X) & ( 1U << (Y) ) ) )
#define WAITCLR( X, Y ) while(  ( (X) & ( 1U << (Y) ) ) )

#define ENTER_CRITICAL(X) __asm("CPSID IF")
#define EXIT_CRITICAL(X) __asm("CPSIE IF")

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


__attribute__((weak))
extern void * memset(void * dest, int ch, size_t len)
{
    uint8_t * d = (uint8_t *)dest;

    while(len > 0U)
    {
        *d = (uint8_t)ch;
        d++;
        len--;
    }

    return dest;
}

#endif /* __UTIL_H_ */
