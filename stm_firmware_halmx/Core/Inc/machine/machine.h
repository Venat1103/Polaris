/*
 * machine.h
 *
 *  Created on: 14-Jul-2026
 *      Author: soham
 */

#ifndef MACHINE_H
#define MACHINE_H

#include "main.h"

extern State flight_states[];
extern Transition flight_transitions[];
extern Flight_Properties flight_properties;
extern FSM machine;

void machine_heartbeat(FSM* fsm);

#endif
