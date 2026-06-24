/*
 * tim.c
 *
 *  Created on: 24-Jun-2026
 *      Author: soham
 */

#include <assert.h>
#include <stdint.h>

#include "stm32f446xx.h"

#include "peripherals/tim.h"
#include "peripherals/rcc.h"

void tim16_init(TIM_TypeDef* tim, uint16_t psc, uint16_t arr) {
    assert(tim != TIM2 && tim != TIM5);

    rcc_tim_enable(tim);
    // set prescalar
    tim->PSC = psc - 1;
    // set autoreload
    tim->ARR = arr;

    // clear counter
    tim->CNT = 0;
    // send prescaler to active register
    tim->EGR = TIM_EGR_UG;
    // clear status register
    tim->SR  = 0;
    // enable
    tim->CR1 = TIM_CR1_CEN;
}

void tim32_init(TIM_TypeDef* tim, uint16_t psc, uint32_t arr) {
    assert(tim == TIM2 || tim == TIM5);

    rcc_tim_enable(tim);
    // set prescalar
    tim->PSC = psc - 1;
    // set autoreload
    tim->ARR = arr;

    // clear counter
    tim->CNT = 0;
    // send prescaler to active register
    tim->EGR = TIM_EGR_UG;
    // clear status register
    tim->SR  = 0;
    // enable
    tim->CR1 = TIM_CR1_CEN;
}

