/*
 * state_functions.c
 *
 *  Created on: 18-Jun-2026
 *      Author: soham
 */

#include <string.h>

#include "machine/state_functions.h"
#include "build_config.h"
#include "main.h"

void enter_standby(void* context) {
    #if defined(DEBUG_LOGGING)
        printf("==========\r\nEnter STANDBY\r\n");
    #endif
    return;
}

void enter_armed(void* context) {
    #if defined(DEBUG_LOGGING)
        printf("==========\r\nEnter ARMED\r\n");
    #endif
    return;
}

void enter_boost(void* context) {
    #if defined(DEBUG_LOGGING)
        printf("==========\r\nEnter BOOST\r\n");
    #endif
    // Flight_Data* data = (Flight_Data*)context;
    // data->baro_altitude = 140.8;
    // data->heading = 10029.5;
    return;
}

void enter_coast(void* context) {
    #if defined(DEBUG_LOGGING)
        printf("==========\r\nEnter COAST\r\n");
    #endif
    // Flight_Data* data = (Flight_Data*)context;
    // data->baro_altitude = 90.8;
    // data->heading = 20029.5;
    return;
}

void enter_drogue(void* context) {
    #if defined(DEBUG_LOGGING)
        printf("==========\r\nEnter DROGUE\r\n");
    #endif
    // Flight_Data* data = (Flight_Data*)context;
    // data->baro_altitude = 0;
    // data->heading = 30029.5;
    return;
}

void enter_main(void* context) {
    #if defined(DEBUG_LOGGING)
        printf("==========\r\nEnter MAIN\r\n");
    #endif
    // Flight_Data* data = (Flight_Data*)context;
    // data->baro_altitude = 80.0;
    // data->heading = 1529.5;
    return;
}

void enter_recovery(void* context) {
    #if defined(DEBUG_LOGGING)
        printf("==========\r\nEnter RECOVERY\r\n");
    #endif
    // Flight_Data* data = (Flight_Data*)context;
    // data->baro_altitude = 0.0;
    // data->heading = 1233.6;
    return;
}
