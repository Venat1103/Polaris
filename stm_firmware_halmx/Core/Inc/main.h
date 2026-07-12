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

/////////////////
// PERIPHERALS //
/////////////////

uint32_t millis();
uint32_t micros();
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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MUX_A_Pin GPIO_PIN_13
#define MUX_A_GPIO_Port GPIOC
#define MUX_C_Pin GPIO_PIN_15
#define MUX_C_GPIO_Port GPIOC
#define MUX_EN_Pin GPIO_PIN_0
#define MUX_EN_GPIO_Port GPIOC
#define PYRO_SENSE_Pin GPIO_PIN_2
#define PYRO_SENSE_GPIO_Port GPIOA
#define ICM_INT_Pin GPIO_PIN_3
#define ICM_INT_GPIO_Port GPIOA
#define Servo2_Pin GPIO_PIN_9
#define Servo2_GPIO_Port GPIOE
#define Servo3_Pin GPIO_PIN_11
#define Servo3_GPIO_Port GPIOE
#define Servo4_Pin GPIO_PIN_13
#define Servo4_GPIO_Port GPIOE
#define Servo5_Pin GPIO_PIN_14
#define Servo5_GPIO_Port GPIOE
#define LSM_INT_Pin GPIO_PIN_12
#define LSM_INT_GPIO_Port GPIOB
#define Servo0_Pin GPIO_PIN_14
#define Servo0_GPIO_Port GPIOB
#define Servo1_Pin GPIO_PIN_15
#define Servo1_GPIO_Port GPIOB
#define Main0_Pin GPIO_PIN_9
#define Main0_GPIO_Port GPIOD
#define Main1_Pin GPIO_PIN_10
#define Main1_GPIO_Port GPIOD
#define Drogue0_Pin GPIO_PIN_14
#define Drogue0_GPIO_Port GPIOD
#define Drogue1_Pin GPIO_PIN_15
#define Drogue1_GPIO_Port GPIOD
#define Fire0_Pin GPIO_PIN_6
#define Fire0_GPIO_Port GPIOC
#define Fire1_Pin GPIO_PIN_7
#define Fire1_GPIO_Port GPIOC
#define LPS_INT_Pin GPIO_PIN_9
#define LPS_INT_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_0
#define BUZZER_GPIO_Port GPIOD
#define STAT1_Pin GPIO_PIN_4
#define STAT1_GPIO_Port GPIOD
#define STAT2_Pin GPIO_PIN_5
#define STAT2_GPIO_Port GPIOD
#define STAT3_Pin GPIO_PIN_6
#define STAT3_GPIO_Port GPIOD
#define STAT4_Pin GPIO_PIN_7
#define STAT4_GPIO_Port GPIOD
#define PB3_Pin GPIO_PIN_3
#define PB3_GPIO_Port GPIOB
#define PB4_Pin GPIO_PIN_4
#define PB4_GPIO_Port GPIOB
#define PB5_Pin GPIO_PIN_5
#define PB5_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
