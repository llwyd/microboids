#include "util.h"
#include "gpio.h"
#include "clock.h"
#include "adc.h"
#include <stdint.h>

#define ADC_BASE ( 0x42004000 )
#define PM_APBC     ( *( ( volatile unsigned int *)0x40000420 ) )

typedef struct
{
    uint8_t CTRLA:8;    /* 0x00 */
    uint8_t REFCTRL:8;  /* 0x01 */
    uint8_t AVGCTRL:8;  /* 0x02 */
    uint8_t SAMPCTRL:8; /* 0x03 */
    uint16_t CTRLB:16;  /* 0x04 */
    uint16_t RESERVED_0:16; 
    uint8_t WINCTRL:8;
    uint8_t RESERVED_1:8;
    uint8_t RESERVED_2:8;
    uint8_t RESERVED_3:8;
    uint8_t SWTRIG:8;
    uint8_t RESERVED_4:8;
    uint8_t RESERVED_5:8;
    uint8_t RESERVED_6:8;
    uint32_t INPUTCTRL:32;
    uint8_t EVCTRL:8;
    uint8_t RESERVED_7:8;
    uint8_t INTENCLR:8;
    uint8_t INTENSET:8;
    uint8_t INTFLAG:8;
    uint8_t STATUS:8;
    uint16_t RESULT:16;
    uint16_t WINLT:16;
    uint16_t RESERVED_8:16;
    uint16_t WINUT:16;
    uint16_t RESERVED_9:16;
    uint16_t GAINCORR:16;
    uint16_t OFFSETCORR:16;
    uint16_t CALIB:16;
    uint8_t DBGCTRL:8;
}
adc_t;

static volatile adc_t * ADC    = ( adc_t * ) ADC_BASE;
static volatile gpio_t * GPIO  = ( gpio_t * ) GPIO_BASE;

extern void ADC_Init( void )
{
    Clock_ConfigureGCLK( 0x7, 0x4, 0x1E );
    PM_APBC |= ( 0x1 << 16U );

    /* PA06 ADC Input, Mux B */
    GPIO->PINCFG6 |= 0x1;
    GPIO->PMUX3 |= 0x1;

    /* Configure for AIN6 */
    /* Ref ctrl 1.65V */
    ADC->REFCTRL |= 0x2;
    
    /* 8bit, free running, div/256 clock */
    ADC->CTRLB |= ( 0x3 << 4 ) | ( 0x1 << 2 ) | ( 0x6 << 8 );

    /* Input control, compare to gnd, input6, divide by 2 gain */
    ADC->INPUTCTRL |= ( 0x18 << 8 ) | ( 0x6 << 0 ) | ( 0xF << 24 );

    /* Enable */
    ADC-> CTRLA |= ( 0x1 << 1 );
}

extern void ADC_Start( void )
{
    /* Start conversion */
    ADC->SWTRIG |= ( 0x1 << 1 );
}



