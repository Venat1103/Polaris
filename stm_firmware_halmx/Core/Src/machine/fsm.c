/*
 * fsm.c
 *
 *  Created on: 17-Jun-2026
 *      Author: soham
 */

#include "machine/fsm.h"

void fsm_heartbeat_core(FSM* fsm) {
    // run function to update current state
    if (fsm->current_state->heartbeat) {
        fsm->current_state->heartbeat(fsm->context);
    }
    if (!fsm->check_transitions) {return;}
    // check for valid transitions
    for (int i = 0; i < fsm->num_transitions; i++) {
        Transition* transition = &fsm->transitions[i];
        if (transition->current == fsm->current_state) {
            if (transition->condition(fsm->context)) {
                // run exit function of current state
                if (fsm->current_state->exit) {
                    fsm->current_state->exit(fsm->context);
                }
                fsm->current_state = transition->next;
                // run enter function of new state
                if (fsm->current_state->enter) {
                    fsm->current_state->enter(fsm->context);
                }
                break;
            }
        }
    }
}
