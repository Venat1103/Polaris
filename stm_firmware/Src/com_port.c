/*
 * com_port.c
 *
 *  Created on: 22-Jun-2026
 *      Author: soham
 */

#include "com_port.h"

void usart2_init() {
    RCC->AHB1ENR |= GPIOA_EN;
    // gpio port A pin 2,3 alternate function mode
    GPIOA->MODER &= GPIO_PIN_2_AF_AND;
    GPIOA->MODER |= GPIO_PIN_2_AF_OR;
    GPIOA->MODER &= GPIO_PIN_3_AF_AND;
    GPIOA->MODER |= GPIO_PIN_3_AF_OR;

    // 0 for afr low, 1 for afr high
    // AF7
    GPIOA->AFR[0] |= (1U << 8);
    GPIOA->AFR[0] |= (1U << 9);
    GPIOA->AFR[0] |= (1U << 10);
    GPIOA->AFR[0] &= ~(1U << 11);

    GPIOA->AFR[0] |= (1U << 12);
    GPIOA->AFR[0] |= (1U << 13);
    GPIOA->AFR[0] |= (1U << 14);
    GPIOA->AFR[0] &= ~(1U << 15);

    /////////

    RCC->APB1ENR |= USART2_EN;
    USART2->BRR = ((APB1_CLK  + (USART_BAUDRATE/2U)) / USART_BAUDRATE);
    USART2->CR1 = CR1_TE_EN;
    USART2->CR1 |= CR1_RE_EN;
    USART2->CR1 |= CR1_USART_EN;
}

void usart2_interrupt_init() {
    RCC->AHB1ENR |= GPIOA_EN;
    // gpio port A pin 2,3 alternate function mode
    GPIOA->MODER &= GPIO_PIN_2_AF_AND;
    GPIOA->MODER |= GPIO_PIN_2_AF_OR;
    GPIOA->MODER &= GPIO_PIN_3_AF_AND;
    GPIOA->MODER |= GPIO_PIN_3_AF_OR;

    // 0 for afr low, 1 for afr high
    // AF7
    GPIOA->AFR[0] |= (1U << 8);
    GPIOA->AFR[0] |= (1U << 9);
    GPIOA->AFR[0] |= (1U << 10);
    GPIOA->AFR[0] &= ~(1U << 11);

    GPIOA->AFR[0] |= (1U << 12);
    GPIOA->AFR[0] |= (1U << 13);
    GPIOA->AFR[0] |= (1U << 14);
    GPIOA->AFR[0] &= ~(1U << 15);

    /////////

    RCC->APB1ENR |= USART2_EN;
    USART2->BRR = ((APB1_CLK  + (USART_BAUDRATE/2U)) / USART_BAUDRATE);
    USART2->CR1 = CR1_TE_EN | CR1_RE_EN;

    // interrupt
    USART2->CR1 |= CR1_RXNEIE_EN;
    NVIC_EnableIRQ(USART2_IRQn);

    USART2->CR1 |= CR1_USART_EN;
}

void usart2_write(int ch) {
    while (!(USART2->SR & SR_TXE)) {}
    USART2->DR = ch;
}

char usart2_read() {
    while (!(USART2->SR & SR_RXNE)) {}
    return USART2->DR;
}
