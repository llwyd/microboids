#ifndef _GPIO_H_
#define _GPIO_H_

#include "util.h"

#define GPIO_BASE   ( 0x41004400 )
#define EIC_BASE    ( 0x40001800 )

typedef struct
{
    unsigned char CTRL:8;
    unsigned char STATUS:8;
    unsigned char NMICTRL:8;
    unsigned char NMIFLAG:8;
    unsigned int EVCTRL:32;
    unsigned int INTENCLR:32;
    unsigned int INTENSET:32;
    unsigned int INTFLAG:32;
    unsigned int WAKEUP:32;
    unsigned int CONFIG0:32;
    unsigned int CONFIG1:32;
}
eic_t;

typedef struct
{
    unsigned int DIRR:32;
    unsigned int DIRCLR:32;
    unsigned int DIRSET:32;
    unsigned int DIRTGL:32;
    unsigned int OUT:32;
    unsigned int OUTCLR:32;
    unsigned int OUTSET:32;
    unsigned int OUTTGL:32;
    unsigned int IN:32;
    unsigned int CTRL:32;
    unsigned int WRCONFIG:32;
    unsigned int RESERVED_0:32;
    unsigned char PMUX0:8;
    unsigned char PMUX1:8;
    unsigned char PMUX2:8;
    unsigned char PMUX3:8;
    unsigned char PMUX4:8;
    unsigned char PMUX5:8;
    unsigned char PMUX6:8;
    unsigned char PMUX7:8;
    unsigned char PMUX8:8;
    unsigned char PMUX9:8;
    unsigned char PMUX10:8;
    unsigned char PMUX11:8;
    unsigned char PMUX12:8;
    unsigned char PMUX13:8;
    unsigned char PMUX14:8;
    unsigned char PMUX15:8;
    unsigned char PINCFG0:8;
    unsigned char PINCFG1:8;
    unsigned char PINCFG2:8;
    unsigned char PINCFG3:8;
    unsigned char PINCFG4:8;
    unsigned char PINCFG5:8;
    unsigned char PINCFG6:8;
    unsigned char PINCFG7:8;
    unsigned char PINCFG8:8;
    unsigned char PINCFG9:8;
    unsigned char PINCFG10:8;
    unsigned char PINCFG11:8;
    unsigned char PINCFG12:8;
    unsigned char PINCFG13:8;
    unsigned char PINCFG14:8;
    unsigned char PINCFG15:8;
    unsigned char PINCFG16:8;
    unsigned char PINCFG17:8;
    unsigned char PINCFG18:8;
    unsigned char PINCFG19:8;
    unsigned char PINCFG20:8;
    unsigned char PINCFG21:8;
    unsigned char PINCFG22:8;
    unsigned char PINCFG23:8;
    unsigned char PINCFG24:8;
    unsigned char PINCFG25:8;
    unsigned char PINCFG26:8;
    unsigned char PINCFG27:8;
    unsigned char PINCFG28:8;
    unsigned char PINCFG29:8;
    unsigned char PINCFG30:8;
    unsigned char PINCFG31:8;
} gpio_t;

#endif /* _GPIO_H_ */
