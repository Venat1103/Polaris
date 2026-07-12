/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "crc.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "quadspi.h"
#include "rtc.h"
#include "sdio.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  while (CDC_Transmit_FS((uint8_t *)ptr, len) == USBD_BUSY)
  {
    HAL_Delay(1);
  }
  return len;
}

uint32_t micros()
{
  return TIM2->CNT;
}

uint32_t millis()
{
  return TIM2->CNT / 1000UL;
}

#if defined(DEBUG_LOGGING)
  uint32_t last_1 = 0;

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

      HAL_GPIO_TogglePin(GPIOA, 5);
    }
  #endif
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  // enable FPU (what a headache this caused)
  SCB->CPACR |= ((3UL << 20) | (3UL << 22));
  __DSB(); // waits until register write is complete
  __ISB(); // flushes and restarts instruction pipeline
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CRC_Init();
  MX_I2C1_Init();
  MX_I2C3_Init();
  MX_QUADSPI_Init();
  MX_SDIO_SD_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_TIM1_Init();
  MX_TIM12_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_TIM2_Init();
  MX_RTC_Init();
  MX_FATFS_Init();
  MX_USB_DEVICE_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  #if defined(DEBUG_LOGGING)
    printf("Debug logging started\r\n");
  #endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    machine.heartbeat(&machine);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
