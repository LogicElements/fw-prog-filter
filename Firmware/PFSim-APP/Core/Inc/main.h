/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RS485_DERE_Pin GPIO_PIN_1
#define RS485_DERE_GPIO_Port GPIOA
#define RS485_D_Pin GPIO_PIN_2
#define RS485_D_GPIO_Port GPIOA
#define RS485_R_Pin GPIO_PIN_3
#define RS485_R_GPIO_Port GPIOA
#define HW_0_Pin GPIO_PIN_12
#define HW_0_GPIO_Port GPIOB
#define LED_R_Pin GPIO_PIN_3
#define LED_R_GPIO_Port GPIOB
#define LED_G_Pin GPIO_PIN_4
#define LED_G_GPIO_Port GPIOB
#define RS485_ADDR4_Pin GPIO_PIN_5
#define RS485_ADDR4_GPIO_Port GPIOB
#define RS485_ADDR3_Pin GPIO_PIN_6
#define RS485_ADDR3_GPIO_Port GPIOB
#define RS485_ADDR2_Pin GPIO_PIN_7
#define RS485_ADDR2_GPIO_Port GPIOB
#define RS485_ADDR1_Pin GPIO_PIN_8
#define RS485_ADDR1_GPIO_Port GPIOB
#define RS485_ADDR0_Pin GPIO_PIN_9
#define RS485_ADDR0_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define SW1_Pin GPIO_PIN_11
#define SW1_GPIO_Port GPIOB
#define SW2_Pin GPIO_PIN_10
#define SW2_GPIO_Port GPIOB

#define EN_5V_Pin GPIO_PIN_10
#define EN_5V_GPIO_Port GPIOA


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
