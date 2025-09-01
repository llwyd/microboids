#include "clock.h"

typedef struct
{
    uint32_t CR:32;
    uint32_t ICSCR:32;
    uint32_t CFGR:32;
    uint32_t PLLCFGR:32;
    uint32_t _RESERVED;
    uint32_t CRRCR:32;
    uint32_t CIER:32;
    uint32_t CIFR:32;
    uint32_t CICR:32;
    uint32_t IOPRSTR:32;
    uint32_t AHBRSTR:32;
    uint32_t APBRSTR1:32;
    uint32_t APBRSTR2:32;
    uint32_t IOPENR:32;
    uint32_t AHBENR:32;
    uint32_t APBENR1:32;
    uint32_t APBENR2:32;
    uint32_t IOPSMENR:32;
    uint32_t AHBSMENR:32;
    uint32_t APBSMENR1:32;
    uint32_t APBSMENR2:32;
    uint32_t CCIPR:32;
    uint32_t CCIPR2:32;
    uint32_t BDCR:32;
    uint32_t CSR:32;
} rcc_t;

#define RCC_BASE   ( 0x40021000 )
static volatile rcc_t * RCC = ( rcc_t * ) RCC_BASE;

void Clock_Set64MHz( void )
{
    /* Increase wait states */
    *((uint32_t *)0x40022000) |= ( 0x2 );
    
    /* R = 2, N = 8, M = 1 */
    RCC->CR &= ~( 0x1 << 24U );
    WAITCLR( RCC->CR, 25U );    

    RCC->PLLCFGR = ( 0x1 << 29 ) | ( 0x1 << 25 ) | ( 0x1 << 17 ) | ( 0x8 << 8 ) /* |  ( 0x1 << 4 )*/ | 0x2;
    
    /* Enable PLL */
    RCC->CR |= ( 0x1 << 24U );
    WAITSET( RCC->CR, 25U );

    /* Enable output R */
    RCC->PLLCFGR |= ( 0x1 << 28U );

    /* Set as system clock */
    RCC->CFGR |= ( 0x2 << 0 );
    while ( ( ( RCC->CFGR >> 3U ) & 0x2 ) != 0x2 );
}
