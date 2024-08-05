#include "gpio.h"

extern void GPIO_Init(void)
{
    /* Lazy way of enabling gpio a and b */
    *((uint32_t *)0x40021034) |= ( 0x1 << 0 );
    *((uint32_t *)0x40021034) |= ( 0x1 << 1 );
}

extern void GPIO_ConfigureOutput(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->MODER &= ~( 1 << ((pin << 1U) + 1U) );
    gpio->MODER |= ( 1 << ((pin << 1U)) );
}

extern void GPIO_Toggle(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->ODR ^= (1 << pin);
}

extern void GPIO_SetOutput(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->ODR |= (1 << pin);
}

extern void GPIO_ClearOutput(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->ODR &= ~(1 << pin);
}

extern void GPIO_SetOpenDrain(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->OTYPER |= ( 1 << pin );
}

extern void GPIO_SetSpeed(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->OSPEEDR |= ( 0x3 << (pin << 1U) );
}

extern void GPIO_SetAlt(volatile gpio_t * const gpio, uint16_t pin, uint8_t alt_func)
{
    gpio->MODER |= ( 1 << ((pin << 1U) + 1U) );
    gpio->MODER &= ~( 1 << ((pin << 1U)) );
   
    //gpio->OTYPER |= (1 << pin);

    if( pin < 8U )
    {
        uint16_t shift = pin * 4U;
        gpio->AFRL &= ~(0xF << shift);
        gpio->AFRL |= (alt_func << shift);
    }
    else
    {
        uint16_t shift = (pin - 8U) * 4U;
        gpio->AFRH &= ~(0xF << shift);
        gpio->AFRH |= (alt_func << shift);
    }
}

