/*
 * dma.h
 *
 *  Created on: 24-Jun-2026
 *      Author: soham
 */

#ifndef DMA_H
#define DMA_H

#include <stdint.h>

#include "stm32f446xx.h"

#define DMA_DIRECTION_PM 0
#define DMA_DIRECTION_MP (1U << 6)

typedef struct {
    DMA_Stream_TypeDef* stream;
    uint32_t channel;
    uint32_t destination;
    uint32_t source;
    uint32_t direction;
} DMA_Config;

void dma_init(DMA_TypeDef* dma, DMA_Config* config);
void dma_transfer(DMA_TypeDef* dma, DMA_Config* config, uint32_t len);

#endif
