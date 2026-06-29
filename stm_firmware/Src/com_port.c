/*
 * com_port.c
 *
 *  Created on: 22-Jun-2026
 *      Author: soham
 */

#include "build_config.h"
#if defined(DEBUG_LOGGING)

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#include "com_port.h"

#include "peripherals/dma.h"
#include "peripherals/gpio.h"
#include "peripherals/usart.h"

DMA_Config dma1_stream6_channel4_config;

#define buffer_size 2048
char buffer[buffer_size];
char master_buffer_1[buffer_size];
char master_buffer_2[buffer_size];
bool master_buffer_1_transmit_ready = true;

void com_port_init() {
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

    dma1_stream6_channel4_config = (DMA_Config){
        DMA1_Stream6,
        4,
        (uint32_t)&USART2->DR,
        (uint32_t)&master_buffer_1,
        DMA_DIRECTION_MP
    };

    dma_init(DMA1, &dma1_stream6_channel4_config);

    // enable USART2 DMA TX request
    USART2->CR3 |= USART_CR3_DMAT;

    USART2->SR  |= USART_SR_TC;   // set TC so first dma_transfer doesn't hang
}

void com_port_log(char* buffer) {
    char* master_buffer;
    if (master_buffer_1_transmit_ready) {
        master_buffer = master_buffer_2;
    } else {
        master_buffer = master_buffer_1;
    }
    strncat(master_buffer, buffer, buffer_size - strlen(master_buffer) - 1);
}

void com_port_transmit(char* buffer) {
    uint32_t len = strlen(buffer);
    if (len < 1) {return;}
    dma1_stream6_channel4_config.source = (uint32_t)buffer;
    // wait for previous DMA transfer to finish
    while (dma1_stream6_channel4_config.stream->CR & DMA_SxCR_EN);
    // wait for USART to finish clocking out last byte
    while (!(USART2->SR & USART_SR_TC));
    USART2->SR &= ~USART_SR_TC;
    dma_transfer(DMA1, &dma1_stream6_channel4_config, len);
}

void com_port_flush() {
    if (master_buffer_1_transmit_ready) {
        com_port_transmit(master_buffer_1);
        master_buffer_1_transmit_ready = !master_buffer_1_transmit_ready;
        master_buffer_1[0] = '\0';
    } else {
        com_port_transmit(master_buffer_2);
        master_buffer_1_transmit_ready = !master_buffer_1_transmit_ready;
        master_buffer_2[0] = '\0';
    }
}

#endif
