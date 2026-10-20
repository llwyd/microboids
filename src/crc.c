#include "crc.h"

#define CRC_BASE ( 0x40023000 )

typedef struct
{
    uint32_t DR:32;
    uint32_t IDR:32;
    uint32_t CR:32;
    uint32_t INIT:32;
    uint32_t POL:32;
} crc_t;

_Static_assert( sizeof( crc_t ) == 20, "CRC struct size incorrect" );

static volatile crc_t * const CRC = ( crc_t * ) CRC_BASE;

extern void CRC_Init(void)
{
    /* Lazy way of enabling CRC */
    *((uint32_t *)0x40021038) |= ( 0x1 << 12 );
}

extern uint32_t CRC_Next(uint32_t input)
{
    CRC->DR = input;

    return CRC->DR;
}
