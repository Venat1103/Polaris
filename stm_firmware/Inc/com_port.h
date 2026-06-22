/*
 * com_port.h
 *
 *  Created on: 22-Jun-2026
 *      Author: soham
 */

#ifndef COM_PORT_H
#define COM_PORT_H

#include "stm32f446xx.h"

void usart2_init();
void usart2_interrupt_init();
void usart2_write(int ch);
char usart2_read();

#define USART2_EN (1U << 17)
#define GPIOA_EN (1U)

#define GPIO_PIN_2_AF_AND ~(1U << 4)
#define GPIO_PIN_2_AF_OR (1U << 5)
#define GPIO_PIN_3_AF_AND ~(1U << 6)
#define GPIO_PIN_3_AF_OR (1U << 7)

#define SR_TXE (1U << 7)
#define SR_RXNE (1U << 5)
#define CR1_TE_EN (1U << 3)
#define CR1_RE_EN (1U << 2)
#define CR1_USART_EN (1U << 13)
#define CR1_RXNEIE_EN (1U << 5)
#define CR1_TCIE_EN (1U << 6)
#define CR1_TXEIE_EN (1U << 7)

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define USART_BAUDRATE 115200

#endif
