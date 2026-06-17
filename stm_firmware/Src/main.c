/*
 * main.c
 *
 *  Created on: 15-Jun-2026
 *      Author: soham
 */

#include <stdint.h>
#include <stdbool.h>

#include "stm32f412rx.h"

#include "fsm.h"

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
    float chamber_pressure;
    float current;
    float voltage;

    float acceleration[3];
    float velocity[3];
    float displacement[3];
    float angular_velocity[3];
    float orientation[3];

    float baro_altitude;
    float gps_altitude;

    float tvc_angle[2];

    float heading;
    float gps_coordinates[2];

    bool motor_continuity[2];
    bool drogue_continuity[2];
    bool main_continuity[2];
} Flight_Data;

int main(void)
{

}
