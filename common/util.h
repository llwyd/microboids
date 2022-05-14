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

#endif /* __UTIL_H_ */
