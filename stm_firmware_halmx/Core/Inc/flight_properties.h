/*
 * flight_properties.h
 *
 *  Created on: 22-Jun-2026
 *      Author: soham
 */

#ifndef FLIGHT_PROPERTIES_H
#define FLIGHT_PROPERTIES_H

#include "build_config.h"

typedef enum {
    Flight_State_Standby,
    Flight_State_Armed,
    Flight_State_Boost,
    Flight_State_Coast,
    Flight_State_Drogue,
    Flight_State_Main,
    Flight_State_Recovery
} Flight_State;

// to be logged onto SD card
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

    #if defined(ACTUATION_THRUST_VECTOR)
        float tvc_angle[2];
    #elif defined(ACTUATION_CONTROL_SURFACE)
        float control_surface_angle[4];
    #endif

    float heading;
    float gps_coordinates[2];
    int gps_lock;
} Flight_Data;

// to be used for internal calculations, not logged onto SD card
typedef struct {
    uint8_t imu0_raw_data[14];
    uint8_t imu0_raw_current_timestamp[3];
    float imu0_temperature; // c
    float imu0_acceleration[3]; // g
    float imu0_angular_velocity[3]; // dps
    uint32_t imu0_last_timestamp; // us
    uint32_t imu0_current_timestamp; // us
    float imu0_velocity[3]; // g * s
    float imu0_displacement[3]; // g * s^2
    float imu0_orientation[3]; // deg

} Flight_Variables;

typedef struct {
    Flight_Data* data;
    Flight_Variables* variables;
} Flight_Properties;

#endif