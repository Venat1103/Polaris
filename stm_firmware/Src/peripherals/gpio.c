/*
 * gpio.c
 *
 *  Created on: 24-Jun-2026
 *      Author: soham
 */

#include "peripherals/gpio.h"

void gpio_set_pin_mode(GPIO_TypeDef* gpio, uint32_t pin, uint32_t mode)
{
    // clear previous value
    gpio->MODER &= ~(3U << (pin * 2));
    // set new value
    gpio->MODER |= (mode << (pin * 2));
}

void gpio_set_pin_af(GPIO_TypeDef* gpio, uint32_t pin, uint32_t af)
{
    gpio_set_pin_mode(gpio, pin, GPIO_MODE_AF);
    // clear previous value
    gpio->AFR[pin / 8] &= ~(0xFU << ((pin % 8) * 4));
    // set new value
    gpio->AFR[pin / 8] |= (af << ((pin % 8) * 4));
}

void gpio_toggle(GPIO_TypeDef* gpio, uint32_t pin)
{
    if (gpio->ODR & (1U << pin)) {
        // reset
        gpio->BSRR = (1U << (pin + 16));
    } else {
        // set
        gpio->BSRR = (1U << pin);
    }
}
