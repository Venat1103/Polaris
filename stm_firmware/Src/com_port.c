/*
 * com_port.c
 *
 *  Created on: 22-Jun-2026
 *      Author: soham
 */

#include "build_config.h"
#if defined(DEBUG_LOGGING)

#include <string.h>

#include "com_port.h"

#include "peripherals/dma.h"
#include "peripherals/gpio.h"
#include "peripherals/usart.h"

void com_port_init(char* buffer) {
    USART_Config usart2_config = {
        USART_BAUDRATE,
        GPIOA,
        2,
        GPIO_AF_7,
        GPIOA,
        3,
        GPIO_AF_7,
    };

    usart_init(USART2, &usart2_config);

    DMA_Config dma1_stream6_channel4_config = {
        DMA1_Stream6,
        4,
        (uint32_t)&USART2->DR,
        (uint32_t)buffer,
        DMA_DIRECTION_MP
    };

    dma_init(DMA1, &dma1_stream6_channel4_config);

    // enable USART2 DMA TX request
    USART2->CR3 |= USART_CR3_DMAT;
}

void com_port_transmit(char* buffer) {
    uint32_t len = strlen(buffer);
    DMA_Config dma1_stream6_channel4_config = {
        DMA1_Stream6,
        4,
        (uint32_t)&USART2->DR,
        (uint32_t)buffer,
        DMA_DIRECTION_MP
    };
    // wait for previous DMA transfer to finish
    while (dma1_stream6_channel4_config.stream->CR & DMA_SxCR_EN);
    // wait for USART to finish clocking out last byte
    while (!(USART2->SR & USART_SR_TC));
    dma_transfer(DMA1, &dma1_stream6_channel4_config, len);
}

#endif
