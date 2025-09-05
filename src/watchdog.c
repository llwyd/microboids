#include "m0_util.h"
#include "util.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define WDOG_BASE ( 0x40003000 )

typedef struct
{
    uint32_t KR:32;
    uint32_t PR:32;
    uint32_t RLR:32;
    uint32_t SR:32;
    uint32_t WINR:32;
}
watchdog_t;


static volatile watchdog_t  * WDOG    = ( watchdog_t * )  WDOG_BASE; 

extern void Watchdog_Init(void)
{
    WDOG->KR = 0x0000CCCC;
    WDOG->KR = 0x00005555;

    WDOG->PR = 2U;
    WDOG->RLR = 0x0FFF;

    while(WDOG->SR != 0U);
    
    WDOG->KR = 0x0000AAAA;
}

extern void Watchdog_Kick(void)
{
    WDOG->KR = 0x0000AAAA;
}

