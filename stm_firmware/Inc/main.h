/*
 * main.h
 *
 *  Created on: 15-Jun-2026
 *      Author: soham
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "machine/fsm.h"

/////////////////////////
// BUILD CONFIGURATION //
/////////////////////////

#include "build_config.h"

///////////////////////
// FLIGHT PORPERTIES //
///////////////////////

#include "flight_properties.h"

/////////////////
// PERIPHERALS //
/////////////////

#define TIM2_PRESCALAR 16 // 1 us per tick
#define TIM2_AUTO_RELOAD_VALUE 0xFFFFFFFFUL

uint32_t millis();
uint32_t micros();

#endif
