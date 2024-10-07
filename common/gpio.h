#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>
#include <stdbool.h>

#if defined TARGET_STM32

typedef struct
{
    uint32_t MODER:32;
    uint32_t OTYPER:32;
    uint32_t OSPEEDR:32;
    uint32_t PUPDR:32;
    uint32_t IDR:32;
    uint32_t ODR:32;
    uint32_t BSRR:32;
    uint32_t LCKR:32;
    uint32_t AFRL:32;
    uint32_t AFRH:32;
    uint32_t BRR:32;
} gpio_t;

#define GPIOA_BASE   ( 0x50000000 )
#define GPIOB_BASE   ( 0x50000400 )
#define GPIOC_BASE   ( 0x50000800 )
#define GPIOD_BASE   ( 0x50000C00 )
#define GPIOE_BASE   ( 0x50001000 )
#define GPIOF_BASE   ( 0x50001400 )

#elif TARGET_SAMD21

#define GPIO_BASE   ( 0x41004400 )
#define EIC_BASE    ( 0x40001800 )

typedef struct
{
    uint8_t CTRL:8;
    uint8_t STATUS:8;
    uint8_t NMICTRL:8;
    uint8_t NMIFLAG:8;
    uint32_t EVCTRL:32;
    uint32_t INTENCLR:32;
    uint32_t INTENSET:32;
    uint32_t INTFLAG:32;
    uint32_t WAKEUP:32;
    uint32_t CONFIG0:32;
    uint32_t CONFIG1:32;
}
eic_t;

typedef struct
{
    uint32_t DIRR:32;
    uint32_t DIRCLR:32;
    uint32_t DIRSET:32;
    uint32_t DIRTGL:32;
    uint32_t OUT:32;
    uint32_t OUTCLR:32;
    uint32_t OUTSET:32;
    uint32_t OUTTGL:32;
    uint32_t IN:32;
    uint32_t CTRL:32;
    uint32_t WRCONFIG:32;
    uint32_t RESERVED_0:32;
    uint8_t PMUX0:8;
    uint8_t PMUX1:8;
    uint8_t PMUX2:8;
    uint8_t PMUX3:8;
    uint8_t PMUX4:8;
    uint8_t PMUX5:8;
    uint8_t PMUX6:8;
    uint8_t PMUX7:8;
    uint8_t PMUX8:8;
    uint8_t PMUX9:8;
    uint8_t PMUX10:8;
    uint8_t PMUX11:8;
    uint8_t PMUX12:8;
    uint8_t PMUX13:8;
    uint8_t PMUX14:8;
    uint8_t PMUX15:8;
    uint8_t PINCFG0:8;
    uint8_t PINCFG1:8;
    uint8_t PINCFG2:8;
    uint8_t PINCFG3:8;
    uint8_t PINCFG4:8;
    uint8_t PINCFG5:8;
    uint8_t PINCFG6:8;
    uint8_t PINCFG7:8;
    uint8_t PINCFG8:8;
    uint8_t PINCFG9:8;
    uint8_t PINCFG10:8;
    uint8_t PINCFG11:8;
    uint8_t PINCFG12:8;
    uint8_t PINCFG13:8;
    uint8_t PINCFG14:8;
    uint8_t PINCFG15:8;
    uint8_t PINCFG16:8;
    uint8_t PINCFG17:8;
    uint8_t PINCFG18:8;
    uint8_t PINCFG19:8;
    uint8_t PINCFG20:8;
    uint8_t PINCFG21:8;
    uint8_t PINCFG22:8;
    uint8_t PINCFG23:8;
    uint8_t PINCFG24:8;
    uint8_t PINCFG25:8;
    uint8_t PINCFG26:8;
    uint8_t PINCFG27:8;
    uint8_t PINCFG28:8;
    uint8_t PINCFG29:8;
    uint8_t PINCFG30:8;
    uint8_t PINCFG31:8;
} gpio_t;

#elif defined TARGET_STM32F4

#define GPIOA_BASE   ( 0x40020000 )
#define GPIOB_BASE   ( 0x40020400 )
#define GPIOC_BASE   ( 0x40020800 )
#define GPIOD_BASE   ( 0x40020C00 )
#define GPIOE_BASE   ( 0x40041000 )

typedef struct
{
    uint32_t MODER:32;
    uint32_t OTYPER:32;
    uint32_t OSPEEDR:32;
    uint32_t PUPDR:32;
    uint32_t IDR:32;
    uint32_t ODR:32;
    uint32_t BSRR:32;
    uint32_t LCKR:32;
    uint32_t AFRL:32;
    uint32_t AFRH:32;
} gpio_t;

#else

_Static_assert(false, "No target defined in gpio.h");

#endif

extern void GPIO_Init(void);
extern void GPIO_ConfigureOutput(volatile gpio_t * const gpio, uint16_t pin);
extern void GPIO_Toggle(volatile gpio_t * const gpio,uint16_t pin);
extern void GPIO_SetAlt(volatile gpio_t * const gpio,uint16_t pin, uint8_t alt_func);
extern void GPIO_SetOutput(volatile gpio_t * const gpio,uint16_t pin);
extern void GPIO_ClearOutput(volatile gpio_t * const gpio,uint16_t pin);
extern void GPIO_SetOpenDrain(volatile gpio_t * const gpio, uint16_t pin);
extern void GPIO_SetSpeed(volatile gpio_t * const gpio, uint16_t pin);


#endif /* _GPIO_H_ */
