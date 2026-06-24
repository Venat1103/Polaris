/*
 * rcc.h
 *
 *  Created on: 24-Jun-2026
 *      Author: soham
 */

#ifndef RCC_H
#define RCC_H

#include <stdint.h>

#include "stm32f446xx.h"

void rcc_enable(volatile uint32_t* reg, uint32_t mask);
void rcc_gpio_enable(GPIO_TypeDef* gpio);
void rcc_tim_enable(TIM_TypeDef* tim);
void rcc_usart_enable(USART_TypeDef* usart);
void rcc_dma_enable(DMA_TypeDef* dma);

#endif
