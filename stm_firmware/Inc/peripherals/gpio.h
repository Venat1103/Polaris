/*
 * gpio.h
 *
 *  Created on: 24-Jun-2026
 *      Author: soham
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#include "stm32f446xx.h"

#define GPIO_MODE_INPUT 0U
#define GPIO_MODE_OUTPUT 1U
#define GPIO_MODE_AF 2U
#define GPIO_MODE_ANALOG 3U

#define GPIO_AF_0 0U
#define GPIO_AF_1 1U
#define GPIO_AF_2 2U
#define GPIO_AF_3 3U
#define GPIO_AF_4 4U
#define GPIO_AF_5 5U
#define GPIO_AF_6 6U
#define GPIO_AF_7 7U
#define GPIO_AF_8 8U
#define GPIO_AF_9 9U
#define GPIO_AF_10 10U
#define GPIO_AF_11 11U
#define GPIO_AF_12 12U
#define GPIO_AF_13 13U
#define GPIO_AF_14 14U
#define GPIO_AF_15 15U

void gpio_set_pin_mode(GPIO_TypeDef* gpio, uint32_t pin, uint32_t mode);
void gpio_set_pin_af(GPIO_TypeDef* gpio, uint32_t pin, uint32_t af);
void gpio_toggle(GPIO_TypeDef* gpio, uint32_t pin);

#endif
