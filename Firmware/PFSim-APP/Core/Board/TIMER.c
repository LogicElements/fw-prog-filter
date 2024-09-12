

#include "configuration.h"
#include "TIMER.h"


 TIM_HandleTypeDef htim1;
 TIM_HandleTypeDef htim2;
 TIM_HandleTypeDef htim3;



void MX_TIM_Set(TimerEnum timer, uint32_t channel, uint32_t frequency)
{

	  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	  TIM_MasterConfigTypeDef sMasterConfig = {0};
	  TIM_OC_InitTypeDef sConfigOC = {0};
	  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

	  uint32_t apb1_clock = 48000000;
	  uint32_t prescaler = 0;
	  uint32_t period = 0;

	  uint32_t divisor = apb1_clock / frequency;
	  period = divisor - 1;
	  prescaler = 0;

	  while (period > 0xFFFF)
	  {
	      prescaler++;
	      period = divisor / (prescaler + 1) - 1;
	  }


    switch (timer)
    {
        case TIMER_1:
            __HAL_RCC_TIM1_CLK_ENABLE();
            htim1.Instance = TIM1;
            break;
        case TIMER_2:
            __HAL_RCC_TIM2_CLK_ENABLE();
            htim2.Instance = TIM2;
            break;
        case TIMER_3:
            __HAL_RCC_TIM3_CLK_ENABLE();
            htim3.Instance = TIM3;
            break;
        default:
            break;
    }

    TIM_HandleTypeDef* htim;
    if (timer == TIMER_1)
        htim = &htim1;
    else if (timer == TIMER_2)
        htim = &htim2;
    else if (timer == TIMER_3)
        htim = &htim3;
    else
        return;

	  htim->Init.Prescaler = prescaler;
	  htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim->Init.Period = period;
	  htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
      htim1.Init.RepetitionCounter = 0;
	  htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

      if (HAL_TIM_Base_Init(htim) != HAL_OK)
      {
        Error_Handler();
      }
      sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
      if (HAL_TIM_ConfigClockSource(htim, &sClockSourceConfig) != HAL_OK)
      {
        Error_Handler();
      }
      if (HAL_TIM_PWM_Init(htim) != HAL_OK)
      {
        Error_Handler();
      }
      sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
      sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
      if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK)
      {
        Error_Handler();
      }

      sConfigOC.OCMode = TIM_OCMODE_PWM1;
      sConfigOC.Pulse = ((period + 1) / 2);  // 50% duty cycle
      sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
      sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
      sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
      sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
      sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
      if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, channel) != HAL_OK)
      {
        Error_Handler();
      }
      sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
      sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
      sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
      sBreakDeadTimeConfig.DeadTime = 0;
      sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
      sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
      sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
      if (HAL_TIMEx_ConfigBreakDeadTime(htim, &sBreakDeadTimeConfig) != HAL_OK)
      {
        Error_Handler();
      }

      HAL_TIM_MspPostInit(htim);
      HAL_TIM_PWM_Start(htim, channel);
}




