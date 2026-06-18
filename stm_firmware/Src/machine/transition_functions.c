/*
 * transition_functions.c
 *
 *  Created on: 18-Jun-2026
 *      Author: soham
 */

#include "machine/transition_functions.h"

bool standby_to_armed(void* context) {
    return false;
}

bool armed_to_boost(void* context) {
    return false;
}

bool boost_to_coast(void* context) {
    return false;
}

bool coast_to_drogue(void* context) {
    return false;
}

bool drogue_to_main(void* context) {
    return false;
}

bool main_to_recovery(void* context) {
    return false;
}
