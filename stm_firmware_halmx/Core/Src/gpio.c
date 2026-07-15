/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MUX_BIT_A_Pin|MUX_BIT_B_Pin|MUX_BIT_C_Pin|MUX_EN_Pin
                          |IGNITER_0_Pin|IGNITER_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, MAIN_PYRO_0_Pin|MAIN_PYRO_1_Pin|DROGUE_PYRO_0_Pin|DROGUE_PYRO_1_Pin
                          |BUZZER_Pin|STAT_LED_0_Pin|STAT_LED_1_Pin|STAT_LED_2_Pin
                          |STAT_LED_3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : MUX_BIT_A_Pin MUX_BIT_B_Pin MUX_BIT_C_Pin IGNITER_0_Pin
                           IGNITER_1_Pin */
  GPIO_InitStruct.Pin = MUX_BIT_A_Pin|MUX_BIT_B_Pin|MUX_BIT_C_Pin|IGNITER_0_Pin
                          |IGNITER_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : MUX_EN_Pin */
  GPIO_InitStruct.Pin = MUX_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MUX_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : IMU0_ICM_INT_Pin BARO1_LPS_INT_Pin */
  GPIO_InitStruct.Pin = IMU0_ICM_INT_Pin|BARO1_LPS_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : IMU1_LSM_INT_Pin */
  GPIO_InitStruct.Pin = IMU1_LSM_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(IMU1_LSM_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MAIN_PYRO_0_Pin MAIN_PYRO_1_Pin DROGUE_PYRO_0_Pin DROGUE_PYRO_1_Pin
                           BUZZER_Pin STAT_LED_0_Pin STAT_LED_1_Pin STAT_LED_2_Pin
                           STAT_LED_3_Pin */
  GPIO_InitStruct.Pin = MAIN_PYRO_0_Pin|MAIN_PYRO_1_Pin|DROGUE_PYRO_0_Pin|DROGUE_PYRO_1_Pin
                          |BUZZER_Pin|STAT_LED_0_Pin|STAT_LED_1_Pin|STAT_LED_2_Pin
                          |STAT_LED_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_CD_Pin */
  GPIO_InitStruct.Pin = SD_CD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SD_CD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3_Pin PB4_Pin PB5_Pin */
  GPIO_InitStruct.Pin = PB3_Pin|PB4_Pin|PB5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
