/*
 * usart.c
 *
 *  Created on: 24-Jun-2026
 *      Author: soham
 */

#include "peripherals/gpio.h"
#include "peripherals/usart.h"
#include "peripherals/rcc.h"

#define APB1_CLK 16000000UL
#define APB2_CLK 16000000UL

uint32_t usart_get_clk(USART_TypeDef* usart) {
    if (usart == USART1 || usart == USART6) {
        return APB2_CLK;
    } else {
        return APB1_CLK;
    }
}

void usart_init(USART_TypeDef* usart, USART_Config* config) {
    // gpio
    rcc_gpio_enable(config->tx_gpio);
    rcc_gpio_enable(config->rx_gpio);
    gpio_set_pin_af(config->tx_gpio, config->tx_pin, config->tx_af);
    gpio_set_pin_af(config->rx_gpio, config->rx_pin, config->rx_af);

    // usart
    rcc_usart_enable(usart);
    usart->BRR = usart_get_clk(usart) / config->baud_rate;
    usart->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void usart_write(USART_TypeDef* usart, char ch) {
    while (!(usart->SR & USART_SR_TXE));
    usart->DR = ch;
}

int usart_read(USART_TypeDef* usart) {
    while (!(usart->SR & USART_SR_RXNE));
    return usart->DR;
}
