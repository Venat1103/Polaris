/*
 * main.c
 *
 *  Created on: 15-Jun-2026
 *      Author: soham
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "stm32f446xx.h"

#include "main.h"

////////////////////////////
// TIMER 2 INTERNAL CLOCK //
////////////////////////////

uint32_t micros() {
    return TIM2->CNT;
}

uint32_t millis() {
    return TIM2->CNT / 1000UL;
}

///////////////////
// DEBUG LOGGING //
///////////////////

#if defined(DEBUG_LOGGING)
    #include "com_port.h"

    // char buffer[512];

    uint32_t last_1 = 0;
    uint32_t last_05 = 0;

    char* get_state_string(Flight_State state) {
        switch (state) {
            case Flight_State_Standby:
                return "Standby";
            case Flight_State_Armed:
                return "Armed";
            case Flight_State_Boost:
                return "Boost";
            case Flight_State_Coast:
                return "Coast";
            case Flight_State_Drogue:
                return "Drogue";
            case Flight_State_Main:
                return "Main";
            case Flight_State_Recovery:
                return "Recovery";
            default:
                return "Unknown";
        }
    }

    int get_decimals(float num, int num_decimals) {
        int factor = 1;
        for (int i = 0; i < num_decimals; i++) {
            factor *= 10;
        }
        return (int)(num * factor) % factor;
    }
#endif

//////////////////////////
// FINITE STATE MACHINE //
//////////////////////////

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
    #if defined(MEASURE_CHAMBER_PRESSURE)
        .chamber_pressure = 4562.984729,
    #endif

    .acceleration = {0.0,0.0,0.0},
    .velocity = {0.0,0.0,0.0},
    .displacement = {0.0,0.0,0.0},
    .angular_velocity = {0.0,0.0,0.0},
    .orientation = {0.0,0.0,0.0},

    .baro_altitude = 0.0,
    .gps_altitude = 0.0,

    #if defined(ACTUATION_THRUST_VECTOR)
        .tvc_angle = {0.0, 0.0},
    #elif defined(ACTUATION_CONTROL_SURFACE)
        .control_surface_angle = {0.0, 0.0, 0.0, 0.0},
    #endif

    .heading = 0.0,
    .gps_coordinates = {0.0,0.0},
    .gps_lock = 5
};

void machine_heartbeat(FSM* fsm);

FSM machine = {
    .states = states,
    .num_states = 7,
    .transitions = transitions,
    .num_transitions = 6,
    .current_state = &states[0],
    .check_transitions = 1,
    .heartbeat = machine_heartbeat,
    .context = &data
};

void machine_heartbeat(FSM* fsm) {
    fsm_heartbeat_core(fsm);
    // run extra code
    Flight_Data* data = (Flight_Data*)fsm->context;
    #if defined(DEBUG_LOGGING)
        if (micros() - last_1 >= 1000000) {
            last_1 = micros();

            sprintf(buffer, "==========\r\nCurrent State: %s\r\n", get_state_string(fsm->current_state->id));
            com_port_log(buffer);

            sprintf(buffer, "Timestamp (s): %lu.%lu\r\n", last_1 / (uint32_t)(1000000), last_1 % (uint32_t)(1000000));
            com_port_log(buffer);

            #if defined(MEASURE_CHAMBER_PRESSURE)
                sprintf(buffer, "Chamber Pressure (bar): %i.%i\r\n", (int)(data->chamber_pressure), get_decimals(data->chamber_pressure, 4));
                com_port_log(buffer);
            #endif

            sprintf(buffer, "Acceleration (m/s^2): %i.%i %i.%i %i.%i\r\n",
                (int)(data->acceleration[0]), get_decimals(data->acceleration[0], 4),
                (int)(data->acceleration[1]), get_decimals(data->acceleration[1], 4),
                (int)(data->acceleration[2]), get_decimals(data->acceleration[2], 4)
            );
            com_port_log(buffer);

            sprintf(buffer, "Velocity (m/s): %i.%i %i.%i %i.%i\r\n",
                (int)(data->velocity[0]), get_decimals(data->velocity[0], 4),
                (int)(data->velocity[1]), get_decimals(data->velocity[1], 4),
                (int)(data->velocity[2]), get_decimals(data->velocity[2], 4)
            );
            com_port_log(buffer);

            sprintf(buffer, "Displacement (m): %i.%i %i.%i %i.%i\r\n",
                (int)(data->displacement[0]), get_decimals(data->displacement[0], 4),
                (int)(data->displacement[1]), get_decimals(data->displacement[1], 4),
                (int)(data->displacement[2]), get_decimals(data->displacement[2], 4)
            );
            com_port_log(buffer);

            sprintf(buffer, "Angular Velocity (o/s): %i.%i %i.%i %i.%i\r\n",
                (int)(data->angular_velocity[0]), get_decimals(data->angular_velocity[0], 4),
                (int)(data->angular_velocity[1]), get_decimals(data->angular_velocity[1], 4),
                (int)(data->angular_velocity[2]), get_decimals(data->angular_velocity[2], 4)
            );
            com_port_log(buffer);

            sprintf(buffer, "Orientation (o): %i.%i %i.%i %i.%i\r\n",
                (int)(data->orientation[0]), get_decimals(data->orientation[0], 4),
                (int)(data->orientation[1]), get_decimals(data->orientation[1], 4),
                (int)(data->orientation[2]), get_decimals(data->orientation[2], 4)
            );
            com_port_log(buffer);

            sprintf(buffer, "Barometer Altitude (feet): %i\r\n", (int)(data->baro_altitude));
            com_port_log(buffer);

            sprintf(buffer, "GPS Altitude (feet): %i\r\n", (int)(data->gps_altitude));
            com_port_log(buffer);

            #if defined(ACTUATION_THRUST_VECTOR)
                sprintf(buffer, "TVC Angle (o): %i.%i %i.%i\r\n",
                    (int)(data->tvc_angle[0]), get_decimals(data->tvc_angle[0], 4),
                    (int)(data->tvc_angle[1]), get_decimals(data->tvc_angle[1], 4)
                );
                com_port_log(buffer);
            #elif defined(ACTUATION_CONTROL_SURFACE)
                sprintf(buffer, "Control Surface Angle (o): %i.%i %i.%i %i.%i %i.%i\r\n",
                    (int)(data->control_surface_angle[0]), get_decimals(data->control_surface_angle[0], 4),
                    (int)(data->control_surface_angle[1]), get_decimals(data->control_surface_angle[1], 4),
                    (int)(data->control_surface_angle[2]), get_decimals(data->control_surface_angle[2], 4),
                    (int)(data->control_surface_angle[3]), get_decimals(data->control_surface_angle[3], 4)
                );
                com_port_log(buffer);
            #endif

            sprintf(buffer, "GPS Heading (o to North): %i.%i\r\n", (int)(data->heading), get_decimals(data->heading, 4));
            com_port_log(buffer);

            sprintf(buffer, "GPS Coordinates (lat, long): %i.%i %i.%i\r\n",
                    (int)(data->gps_coordinates[0]), get_decimals(data->gps_coordinates[0], 6),
                    (int)(data->gps_coordinates[1]), get_decimals(data->gps_coordinates[1], 6)
                );
            com_port_log(buffer);

            sprintf(buffer, "GPS Lock: %i Satellites\r\n", data->gps_lock);
            com_port_log(buffer);

            com_port_flush();
            gpio_toggle(GPIOA, 5);
        }
    #endif
}

//////////
// MAIN //
//////////

int main() {
    // enable FPU (what a headache this caused)
    SCB->CPACR |= ((3UL << 20) | (3UL << 22));
    __DSB(); // waits until register write is complete
    __ISB(); // flushes and restarts instruction pipeline

    #if defined(DEBUG_LOGGING)
        com_port_init();
        sprintf(buffer, "Debug logging started\r\n");
        com_port_log(buffer);
        // com_port_flush();
        gpio_set_pin_mode(GPIOA, 5, GPIO_MODE_OUTPUT);
    #endif
    // Start TIM2 as master clock, correct by RTC for drift
    tim32_init(TIM2, TIM2_PRESCALAR, TIM2_AUTO_RELOAD_VALUE);
    while(1) {
        machine.heartbeat(&machine);
    }
    return 0;
}
