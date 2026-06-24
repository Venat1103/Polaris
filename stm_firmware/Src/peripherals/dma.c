/*
 * dma.c
 *
 *  Created on: 24-Jun-2026
 *      Author: soham
 */

#include <stdint.h>

#include "stm32f446xx.h"

#include "peripherals/dma.h"
#include "peripherals/rcc.h"

void dma_clear_flags(DMA_TypeDef* dma, DMA_Stream_TypeDef* stream) {
    // streams 0-3 use LIFCR, streams 4-7 use HIFCR
    // non-uniform offsets: stream 0/4=0, 1/5=6, 2/6=16, 3/7=22
    uint32_t offsets[] = { 0, 6, 16, 22, 0, 6, 16, 22 };

    uint32_t index;
    if (stream == DMA1_Stream0 || stream == DMA2_Stream0) {
        index = 0;
    } else if (stream == DMA1_Stream1 || stream == DMA2_Stream1) {
        index = 1;
    } else if (stream == DMA1_Stream2 || stream == DMA2_Stream2) {
        index = 2;
    } else if (stream == DMA1_Stream3 || stream == DMA2_Stream3) {
        index = 3;
    } else if (stream == DMA1_Stream4 || stream == DMA2_Stream4) {
        index = 4;
    } else if (stream == DMA1_Stream5 || stream == DMA2_Stream5) {
        index = 5;
    } else if (stream == DMA1_Stream6 || stream == DMA2_Stream6) {
        index = 6;
    } else {
        index = 7;
    }

    uint32_t shift = offsets[index];
    volatile uint32_t* fcr = (index < 4) ? &dma->LIFCR : &dma->HIFCR;

    *fcr = (1U << shift) |
        (1U << (shift + 1)) |
        (1U << (shift + 2)) |
        (1U << (shift + 3)) |
        (1U << (shift + 5));
}

void dma_init(DMA_TypeDef* dma, DMA_Config* config) {
    rcc_dma_enable(dma);

    // disable stream and wait
    config->stream->CR &= ~DMA_SxCR_EN;
    while (config->stream->CR & DMA_SxCR_EN);

    dma_clear_flags(dma, config->stream);

    config->stream->PAR  = config->destination;
    config->stream->M0AR = config->source;
    config->stream->CR   = (config->channel << 25) |
        config->direction |
        DMA_SxCR_MINC;
    config->stream->FCR  = 0;
}

void dma_transfer(DMA_TypeDef* dma, DMA_Config* config, uint32_t len) {
    while (config->stream->CR & DMA_SxCR_EN);

    dma_clear_flags(dma, config->stream);

    config->stream->PAR  = config->destination;
    config->stream->M0AR = config->source;
    config->stream->NDTR = len;
    config->stream->CR  |= DMA_SxCR_EN;
}