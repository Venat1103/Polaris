/*
 * state_functions.h
 *
 *  Created on: 18-Jun-2026
 *      Author: soham
 */

#ifndef STATE_FUNCTIONS_H
#define STATE_FUNCTIONS_H

#include "machine/fsm.h"

void enter_standby(void* context);
void enter_armed(void* context);
void enter_boost(void* context);
void enter_coast(void* context);
void enter_drogue(void* context);
void enter_main(void* context);
void enter_recovery(void* context);

#endif
