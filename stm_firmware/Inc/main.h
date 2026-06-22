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

void tim2_1mhz_init(void);

#endif
