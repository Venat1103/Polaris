/*
 * transition_functions.c
 *
 *  Created on: 18-Jun-2026
 *      Author: soham
 */

#include <stdint.h>

#include "main.h"
#include "machine/transition_functions.h"

bool standby_to_armed(void* context) {
    if (micros() > (10 * 1000000)) {
        return true;
    }
    return false;
}

bool armed_to_boost(void* context) {
    if (micros() > (20 * 1000000)) {
        return true;
    }
    return false;
}

bool boost_to_coast(void* context) {
    if (micros() > (30 * 1000000)) {
        return true;
    }
    return false;
}

bool coast_to_drogue(void* context) {
    if (micros() > (40 * 1000000)) {
        return true;
    }
    return false;
}

bool drogue_to_main(void* context) {
    if (micros() > (50 * 1000000)) {
        return true;
    }
    return false;
}

bool main_to_recovery(void* context) {
    if (micros() > (60 * 1000000)) {
        return true;
    }
    return false;
}
