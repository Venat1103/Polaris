/*
 * machine.h
 *
 *  Created on: 18-Jun-2026
 *      Author: soham
 */

#ifndef MACHINE_H
#define MACHINE_H

#include <stdbool.h>

#include "machine/fsm.h"
#include "machine/state_functions.h"
#include "machine/transition_functions.h"

State states[] = {
    {Flight_State_Standby, NULL, enter_standby, NULL},
    {Flight_State_Armed, NULL, enter_armed, NULL},
    {Flight_State_Boost, NULL, enter_boost, NULL},
    {Flight_State_Coast, NULL, enter_coast, NULL},
    {Flight_State_Drogue, NULL, enter_drogue, NULL},
    {Flight_State_Main, NULL, enter_main, NULL},
    {Flight_State_Recovery, NULL, enter_recovery, NULL}
};

Transition transitions[] = {
    {&states[0], &states[1], standby_to_armed},
    {&states[1], &states[2], armed_to_boost},
    {&states[2], &states[3], boost_to_coast},
    {&states[3], &states[4], coast_to_drogue},
    {&states[4], &states[5], drogue_to_main},
    {&states[5], &states[6], main_to_recovery}
};

Flight_Data data = {
    0.0,
    0.0,
    0.0,

    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},

    0.0,
    0.0,

    #if defined(CONTROL_TVC)
        {0.0, 0.0},
    #elif defined(CONTROL_SURFACE)
        {0.0, 0.0, 0.0, 0.0},
    #endif

    0.0,
    {0.0,0.0},
    0
};

void fsm_update(FSM* fsm) {
    fsm_update_core(fsm);
    // run extra code
    // printf("Current State: %i\nCurrent: %.2f, Voltage: %.2f\n", fsm->current_state->id, data.current, data.voltage);
}

FSM machine = {
    states,
    7,
    transitions,
    6,
    &states[0],
    1,
    fsm_update,
    &data
};

#endif
