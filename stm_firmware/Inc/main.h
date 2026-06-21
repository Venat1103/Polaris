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

#define MEASURE_CHAMBER_PRESSURE
#define CONTROL_TVC
// #define CONTROL_SURFACE

#if defined(CONTROL_TVC) && defined(CONTROL_SURFACE)
    #error "Cannot define both CONTROL_TVC and CONTROL_SURFACE"
#endif

#if defined(CONTROL_TVC)
    #warning "Using thrust vector control"
#elif defined(CONTROL_SURFACE)
    #warning "Using control surface"
#else
    #warning "No control mode selected"
#endif

typedef enum {
    Flight_State_Standby,
    Flight_State_Armed,
    Flight_State_Boost,
    Flight_State_Coast,
    Flight_State_Drogue,
    Flight_State_Main,
    Flight_State_Recovery
} Flight_State;

typedef struct {
    #if defined(MEASURE_CHAMBER_PRESSURE)
        float chamber_pressure;
    #endif

    float acceleration[3];
    float velocity[3];
    float displacement[3];
    float angular_velocity[3];
    float orientation[3];

    float baro_altitude;
    float gps_altitude;

    #if defined(CONTROL_TVC)
        float tvc_angle[2];
    #elif defined(CONTROL_SURFACE)
        float control_surface_angle[4];
    #endif

    float heading;
    float gps_coordinates[2];
    int gps_lock;
} Flight_Data;

/////////////////
// PERIPHERALS //
/////////////////

void tim2_1mhz_init(void);

#endif
