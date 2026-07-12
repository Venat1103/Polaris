/*
 * transition_functions.h
 *
 *  Created on: 18-Jun-2026
 *      Author: soham
 */

#ifndef TRANSITION_FUNCTIONS_H
#define TRANSITION_FUNCTIONS_H

#include <stdbool.h>

#include "machine/fsm.h"

bool standby_to_armed(void* context);
bool armed_to_boost(void* context);
bool boost_to_coast(void* context);
bool coast_to_drogue(void* context);
bool drogue_to_main(void* context);
bool main_to_recovery(void* context);

#endif
