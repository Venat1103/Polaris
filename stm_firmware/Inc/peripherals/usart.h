/*
 * usart.h
 *
 *  Created on: 24-Jun-2026
 *      Author: soham
 */

#ifndef USART_H
#define USART_H

#include <stdint.h>

#include "stm32f446xx.h"

typedef struct {
    uint32_t baud_rate;
    GPIO_TypeDef* tx_gpio;
    uint32_t tx_pin;
    uint32_t tx_af;
    GPIO_TypeDef* rx_gpio;
    uint32_t rx_pin;
    uint32_t rx_af;
} USART_Config;

void usart_init(USART_TypeDef* usart, USART_Config* config);
void usart_write(USART_TypeDef* usart, char ch);
int usart_read(USART_TypeDef* usart);

#endif
