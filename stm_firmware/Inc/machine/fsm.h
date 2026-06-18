/*
 * fsm.h
 *
 *  Created on: 17-Jun-2026
 *      Author: soham
 */

#ifndef FSM_H
#define FSM_H

#include <stdint.h>
#include <stdbool.h>

typedef struct FSM FSM;

typedef struct {
    uint32_t id; // can be used to store enum value
    void (*update)(void* context); // function to execute periodically when in this state
    void (*enter)(void* context);  // function to execute when entering this state
    void (*exit)(void* context);   // function to execute when exiting this state
} State;

typedef struct {
    State* current;
    State* next;
    bool (*condition)(void* context); // check for valid transitions per fsm update
} Transition;

struct FSM {
    State* states;
    int num_states;
    Transition* transitions;
    int num_transitions;
    State* current_state;
    int check_transitions; // flag to check for valid transitions, save compute power when required
    void (*update)(FSM* fsm); // function to update the FSM periodically
    void* context; // user-defined context for the FSM, should contain any necessary data for the states and transitions
};

void fsm_update_core(FSM* fsm);

#endif
