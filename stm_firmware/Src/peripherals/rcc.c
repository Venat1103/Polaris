/*
 * rcc.c
 *
 *  Created on: 24-Jun-2026
 *      Author: soham
 */

#include "peripherals/rcc.h"

void rcc_enable(volatile uint32_t* reg, uint32_t mask) {
    *reg |= mask;
    (void)*reg;  // dummy read to let clock stabilize
}

void rcc_gpio_enable(GPIO_TypeDef* gpio) {
    if (gpio == GPIOA) {
        rcc_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
    } else if (gpio == GPIOB) {
        rcc_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
    } else if (gpio == GPIOC) {
        rcc_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
    } else if (gpio == GPIOD) {
        rcc_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
    } else if (gpio == GPIOE) {
        rcc_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
    } else if (gpio == GPIOF) {
        rcc_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);
    } else if (gpio == GPIOG) {
        rcc_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
    } else if (gpio == GPIOH) {
        rcc_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);
    }
}

void rcc_tim_enable(TIM_TypeDef* tim) {
    if (tim == TIM1) {
        rcc_enable(&RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
    } else if (tim == TIM2) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
    } else if (tim == TIM3) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
    } else if (tim == TIM4) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_TIM4EN);
    } else if (tim == TIM5) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_TIM5EN);
    } else if (tim == TIM6) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_TIM6EN);
    } else if (tim == TIM7) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_TIM7EN);
    } else if (tim == TIM8) {
        rcc_enable(&RCC->APB2ENR, RCC_APB2ENR_TIM8EN);
    } else if (tim == TIM9) {
        rcc_enable(&RCC->APB2ENR, RCC_APB2ENR_TIM9EN);
    } else if (tim == TIM10) {
        rcc_enable(&RCC->APB2ENR, RCC_APB2ENR_TIM10EN);
    } else if (tim == TIM11) {
        rcc_enable(&RCC->APB2ENR, RCC_APB2ENR_TIM11EN);
    } else if (tim == TIM12) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_TIM12EN);
    } else if (tim == TIM13) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_TIM13EN);
    } else if (tim == TIM14) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_TIM14EN);
    }
}

void rcc_usart_enable(USART_TypeDef* usart) {
    if (usart == USART1) {
        rcc_enable(&RCC->APB2ENR, RCC_APB2ENR_USART1EN);
    } else if (usart == USART2) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_USART2EN);
    } else if (usart == USART3) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_USART3EN);
    } else if (usart == UART4) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_UART4EN);
    } else if (usart == UART5) {
        rcc_enable(&RCC->APB1ENR, RCC_APB1ENR_UART5EN);
    } else if (usart == USART6) {
        rcc_enable(&RCC->APB2ENR, RCC_APB2ENR_USART6EN);
    }
}

void rcc_dma_enable(DMA_TypeDef* dma) {
    if (dma == DMA1) {
        rcc_enable(&RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN);
    } else if (dma == DMA2) {
        rcc_enable(&RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN);
    }
}
