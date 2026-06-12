#include "gpio.h"

extern void GPIO_Init(void)
{
    /* Lazy way of enabling gpio a and b */
    *((uint32_t *)0x40021034) |= ( 0x1 << 0 );
    *((uint32_t *)0x40021034) |= ( 0x1 << 1 );
}

extern void GPIO_ConfigureOutput(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->MODER &= (uint32_t)~( 1u << ((uint32_t)(pin << 1U) + 1U) );
    gpio->MODER |= (uint32_t)( 1u << ((pin << 1U)) );
}

extern void GPIO_ConfigureInput(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->MODER &= (uint32_t)~( 1u << ((uint32_t)(pin << 1U) + 1U) );
    gpio->MODER &= (uint32_t)~( 1u << ((uint32_t)(pin << 1U)) );
    
    gpio->PUPDR &= (uint32_t)~( 1u << ((uint32_t)(pin << 1U) + 1U) );
    gpio->PUPDR &= (uint32_t)~( 1u << ((uint32_t)(pin << 1U)) );
}

extern bool GPIO_ReadInput(volatile gpio_t * const gpio, uint16_t pin)
{
    return (bool)((gpio->IDR >> pin) & 1u);
}

extern void GPIO_Toggle(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->ODR ^= (uint32_t)(1u << pin);
}

extern void GPIO_SetOutput(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->ODR |= (uint32_t)(1u << pin);
}

extern void GPIO_ClearOutput(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->ODR &= (uint32_t)~(1u << pin);
}

extern void GPIO_SetOpenDrain(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->OTYPER |= (uint32_t)( 1u << pin );
}

extern void GPIO_SetSpeed(volatile gpio_t * const gpio, uint16_t pin)
{
    gpio->OSPEEDR |= (uint32_t)( 0x3u << (uint32_t)(pin << 1U) );
}

extern void GPIO_SetAlt(volatile gpio_t * const gpio, uint16_t pin, uint8_t alt_func)
{
    gpio->MODER |= (uint32_t)( 1u << ((uint32_t)(pin << 1U) + 1U) );
    gpio->MODER &= (uint32_t)~( 1u << ((uint32_t)(pin << 1U)) );
   
    //gpio->OTYPER |= (1 << pin);

    if( pin < 8U )
    {
        uint32_t shift = (uint32_t)pin * 4u;
        gpio->AFRL &= (uint32_t)~(0xF << shift);
        gpio->AFRL |= (uint32_t)(alt_func << shift);
    }
    else
    {
        uint32_t shift = ((uint32_t)pin - 8u) * 4u;
        gpio->AFRH &= (uint32_t)~(0xF << shift);
        gpio->AFRH |= (uint32_t)(alt_func << shift);
    }
}

