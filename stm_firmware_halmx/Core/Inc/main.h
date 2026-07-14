/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f446xx.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/////////////////////////
// BUILD CONFIGURATION //
/////////////////////////

#include "build_config.h"

///////////////////////
// FLIGHT PORPERTIES //
///////////////////////

#include "flight_properties.h"

//////////////////////////
// FINITE STATE MACHINE //
//////////////////////////

#include "machine/fsm.h"
#include "machine/state_functions.h"
#include "machine/transition_functions.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/////////////////
// PERIPHERALS //
/////////////////

uint32_t millis();
uint32_t micros();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MUX_BIT_A_Pin GPIO_PIN_13
#define MUX_BIT_A_GPIO_Port GPIOC
#define MUX_BIT_B_Pin GPIO_PIN_14
#define MUX_BIT_B_GPIO_Port GPIOC
#define MUX_BIT_C_Pin GPIO_PIN_15
#define MUX_BIT_C_GPIO_Port GPIOC
#define MUX_EN_Pin GPIO_PIN_0
#define MUX_EN_GPIO_Port GPIOC
#define IMU1_LSM_MISO_Pin GPIO_PIN_2
#define IMU1_LSM_MISO_GPIO_Port GPIOC
#define IMU1_LSM_MOSI_Pin GPIO_PIN_3
#define IMU1_LSM_MOSI_GPIO_Port GPIOC
#define GNSS_TX_Pin GPIO_PIN_0
#define GNSS_TX_GPIO_Port GPIOA
#define GNSS_RX_Pin GPIO_PIN_1
#define GNSS_RX_GPIO_Port GPIOA
#define PYRO_SENSE_Pin GPIO_PIN_2
#define PYRO_SENSE_GPIO_Port GPIOA
#define IMU0_ICM_INT_Pin GPIO_PIN_3
#define IMU0_ICM_INT_GPIO_Port GPIOA
#define IMU0_ICM_INT_EXTI_IRQn EXTI3_IRQn
#define IMU0_ICM_NSS_Pin GPIO_PIN_4
#define IMU0_ICM_NSS_GPIO_Port GPIOA
#define IMU0_ICM_SCK_Pin GPIO_PIN_5
#define IMU0_ICM_SCK_GPIO_Port GPIOA
#define IMU0_ICM_MISO_Pin GPIO_PIN_6
#define IMU0_ICM_MISO_GPIO_Port GPIOA
#define IMU0_ICM_MOSI_Pin GPIO_PIN_7
#define IMU0_ICM_MOSI_GPIO_Port GPIOA
#define RF_RX_Pin GPIO_PIN_7
#define RF_RX_GPIO_Port GPIOE
#define RF_TX_Pin GPIO_PIN_8
#define RF_TX_GPIO_Port GPIOE
#define SERVO_2_Pin GPIO_PIN_9
#define SERVO_2_GPIO_Port GPIOE
#define SERVO_3_Pin GPIO_PIN_11
#define SERVO_3_GPIO_Port GPIOE
#define SERVO_4_Pin GPIO_PIN_13
#define SERVO_4_GPIO_Port GPIOE
#define SERVO_5_Pin GPIO_PIN_14
#define SERVO_5_GPIO_Port GPIOE
#define IMU1_LSM_INT_Pin GPIO_PIN_12
#define IMU1_LSM_INT_GPIO_Port GPIOB
#define IMU1_LSM_INT_EXTI_IRQn EXTI15_10_IRQn
#define IMU1_LSM_SCK_Pin GPIO_PIN_13
#define IMU1_LSM_SCK_GPIO_Port GPIOB
#define SERVO_0_Pin GPIO_PIN_14
#define SERVO_0_GPIO_Port GPIOB
#define SERVO_1_Pin GPIO_PIN_15
#define SERVO_1_GPIO_Port GPIOB
#define MAIN_PYRO_0_Pin GPIO_PIN_9
#define MAIN_PYRO_0_GPIO_Port GPIOD
#define MAIN_PYRO_1_Pin GPIO_PIN_10
#define MAIN_PYRO_1_GPIO_Port GPIOD
#define DROGUE_PYRO_0_Pin GPIO_PIN_14
#define DROGUE_PYRO_0_GPIO_Port GPIOD
#define DROGUE_PYRO_1_Pin GPIO_PIN_15
#define DROGUE_PYRO_1_GPIO_Port GPIOD
#define IGNITER_0_Pin GPIO_PIN_6
#define IGNITER_0_GPIO_Port GPIOC
#define IGNITER_1_Pin GPIO_PIN_7
#define IGNITER_1_GPIO_Port GPIOC
#define BARO1_LPS_SDA_Pin GPIO_PIN_9
#define BARO1_LPS_SDA_GPIO_Port GPIOC
#define BARO1_LPS_SCL_Pin GPIO_PIN_8
#define BARO1_LPS_SCL_GPIO_Port GPIOA
#define BARO1_LPS_INT_Pin GPIO_PIN_9
#define BARO1_LPS_INT_GPIO_Port GPIOA
#define BARO1_LPS_INT_EXTI_IRQn EXTI9_5_IRQn
#define BUZZER_Pin GPIO_PIN_0
#define BUZZER_GPIO_Port GPIOD
#define SD_CD_Pin GPIO_PIN_1
#define SD_CD_GPIO_Port GPIOD
#define STAT_LED_0_Pin GPIO_PIN_4
#define STAT_LED_0_GPIO_Port GPIOD
#define STAT_LED_1_Pin GPIO_PIN_5
#define STAT_LED_1_GPIO_Port GPIOD
#define STAT_LED_2_Pin GPIO_PIN_6
#define STAT_LED_2_GPIO_Port GPIOD
#define STAT_LED_3_Pin GPIO_PIN_7
#define STAT_LED_3_GPIO_Port GPIOD
#define PB3_Pin GPIO_PIN_3
#define PB3_GPIO_Port GPIOB
#define PB4_Pin GPIO_PIN_4
#define PB4_GPIO_Port GPIOB
#define PB5_Pin GPIO_PIN_5
#define PB5_GPIO_Port GPIOB
#define BARO0_MS_SDA_Pin GPIO_PIN_7
#define BARO0_MS_SDA_GPIO_Port GPIOB
#define BARO0_MS_SCL_Pin GPIO_PIN_8
#define BARO0_MS_SCL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
