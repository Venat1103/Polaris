/*
 * tim.h
 *
 *  Created on: 24-Jun-2026
 *      Author: soham
 */

#ifndef TIM_H
#define TIM_H

#include <stdint.h>

#include "stm32f446xx.h"

void tim16_init(TIM_TypeDef* tim, uint16_t psc, uint16_t arr);
void tim32_init(TIM_TypeDef* tim, uint16_t psc, uint32_t arr);

#endif
