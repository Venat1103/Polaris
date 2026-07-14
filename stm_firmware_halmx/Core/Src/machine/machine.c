/*
 * machine.c
 *
 *  Created on: 14-Jul-2026
 *      Author: soham
 */

#include "main.h"

State flight_states[] = {
  {Flight_State_Standby, NULL, enter_standby, NULL},
  {Flight_State_Armed, NULL, enter_armed, NULL},
  {Flight_State_Boost, NULL, enter_boost, NULL},
  {Flight_State_Coast, NULL, enter_coast, NULL},
  {Flight_State_Drogue, NULL, enter_drogue, NULL},
  {Flight_State_Main, NULL, enter_main, NULL},
  {Flight_State_Recovery, NULL, enter_recovery, NULL}
};

Transition flight_transitions[] = {
  {&flight_states[0], &flight_states[1], standby_to_armed},
  {&flight_states[1], &flight_states[2], armed_to_boost},
  {&flight_states[2], &flight_states[3], boost_to_coast},
  {&flight_states[3], &flight_states[4], coast_to_drogue},
  {&flight_states[4], &flight_states[5], drogue_to_main},
  {&flight_states[5], &flight_states[6], main_to_recovery}
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

Flight_Variables variables = {
  .imu0_raw_data = {0},
  .imu0_raw_current_timestamp = {0},
  .imu0_temperature = 0.0,
  .imu0_acceleration = {0.0, 0.0, 0.0},
  .imu0_angular_velocity = {0.0, 0.0, 0.0},
  .imu0_last_timestamp = 0,
  .imu0_current_timestamp = 0,
  .imu0_velocity = {0.0, 0.0, 0.0},
  .imu0_displacement = {0.0, 0.0, 0.0},
  .imu0_orientation = {0.0, 0.0, 0.0}
};

Flight_Properties flight_properties = {
  .data = &data,
  .variables = &variables
};

void machine_heartbeat(FSM* fsm);

FSM machine = {
  .states = flight_states,
  .num_states = 7,
  .transitions = flight_transitions,
  .num_transitions = 6,
  .current_state = &flight_states[0],
  .check_transitions = 1,
  .heartbeat = machine_heartbeat,
  .context = &flight_properties
};

void machine_heartbeat(FSM* fsm) {
  fsm_heartbeat_core(fsm);
  // run extra code
  Flight_Properties* flight_props = (Flight_Properties*)fsm->context;
  Flight_Data* data = flight_props->data;
  #if defined(DEBUG_LOGGING)
    if (micros() - last_1 >= 1000000) {
      last_1 = micros();

      printf("==========\r\nCurrent State: %s\r\n", get_state_string(fsm->current_state->id));

      printf("Timestamp (s): %lu.%lu\r\n", last_1 / (uint32_t)(1000000), last_1 % (uint32_t)(1000000));

      #if defined(MEASURE_CHAMBER_PRESSURE)
        printf("Chamber Pressure (bar): %i.%i\r\n", (int)(data->chamber_pressure), get_decimals(data->chamber_pressure, 4));
      #endif

      printf("Acceleration (m/s^2): %i.%i %i.%i %i.%i\r\n",
        (int)(data->acceleration[0]), get_decimals(data->acceleration[0], 4),
        (int)(data->acceleration[1]), get_decimals(data->acceleration[1], 4),
        (int)(data->acceleration[2]), get_decimals(data->acceleration[2], 4)
      );

      printf("Velocity (m/s): %i.%i %i.%i %i.%i\r\n",
        (int)(data->velocity[0]), get_decimals(data->velocity[0], 4),
        (int)(data->velocity[1]), get_decimals(data->velocity[1], 4),
        (int)(data->velocity[2]), get_decimals(data->velocity[2], 4)
      );

      printf("Displacement (m): %i.%i %i.%i %i.%i\r\n",
        (int)(data->displacement[0]), get_decimals(data->displacement[0], 4),
        (int)(data->displacement[1]), get_decimals(data->displacement[1], 4),
        (int)(data->displacement[2]), get_decimals(data->displacement[2], 4)
      );

      printf("Angular Velocity (o/s): %i.%i %i.%i %i.%i\r\n",
        (int)(data->angular_velocity[0]), get_decimals(data->angular_velocity[0], 4),
        (int)(data->angular_velocity[1]), get_decimals(data->angular_velocity[1], 4),
        (int)(data->angular_velocity[2]), get_decimals(data->angular_velocity[2], 4)
      );

      printf("Orientation (o): %i.%i %i.%i %i.%i\r\n",
        (int)(data->orientation[0]), get_decimals(data->orientation[0], 4),
        (int)(data->orientation[1]), get_decimals(data->orientation[1], 4),
        (int)(data->orientation[2]), get_decimals(data->orientation[2], 4)
      );

      printf("Barometer Altitude (feet): %i\r\n", (int)(data->baro_altitude));

      printf("GPS Altitude (feet): %i\r\n", (int)(data->gps_altitude));

      #if defined(ACTUATION_THRUST_VECTOR)
        printf("TVC Angle (o): %i.%i %i.%i\r\n",
          (int)(data->tvc_angle[0]), get_decimals(data->tvc_angle[0], 4),
          (int)(data->tvc_angle[1]), get_decimals(data->tvc_angle[1], 4)
          );
      #elif defined(ACTUATION_CONTROL_SURFACE)
        printf("Control Surface Angle (o): %i.%i %i.%i %i.%i %i.%i\r\n",
          (int)(data->control_surface_angle[0]), get_decimals(data->control_surface_angle[0], 4),
          (int)(data->control_surface_angle[1]), get_decimals(data->control_surface_angle[1], 4),
          (int)(data->control_surface_angle[2]), get_decimals(data->control_surface_angle[2], 4),
          (int)(data->control_surface_angle[3]), get_decimals(data->control_surface_angle[3], 4)
          );
      #endif

      printf("GPS Heading (o to North): %i.%i\r\n", (int)(data->heading), get_decimals(data->heading, 4));

      printf("GPS Coordinates (lat, long): %i.%i %i.%i\r\n",
          (int)(data->gps_coordinates[0]), get_decimals(data->gps_coordinates[0], 6),
          (int)(data->gps_coordinates[1]), get_decimals(data->gps_coordinates[1], 6)
        );

      printf("GPS Lock: %i Satellites\r\n", data->gps_lock);

      HAL_GPIO_TogglePin(STAT_LED_0_GPIO_Port, STAT_LED_0_Pin);
    }
  #endif
}
