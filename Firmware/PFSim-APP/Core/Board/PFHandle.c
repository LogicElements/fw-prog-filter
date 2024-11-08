/*
 * PFHandle.c
 *
 *  Created on: Aug 29, 2024
 *      Author: evzen
 */

#include "configuration.h"
#include "PFHandle.h"
#include "Timer.h"
#include "main.h"


typedef struct
{
	uint32_t LPfrequency;
	uint32_t HPfrequency;
	uint32_t FreqRatioLP;
	uint32_t FreqRatioHP;
	uint8_t previous_reset_state;
	uint8_t current_reset_state;
}PF_t;

static PF_t pf_app;


void PFInit(void)
{
  /* Restore default values */
  conf.pf.cutoff_hp = conf.pf.def_cutoff_hp;
  conf.pf.cutoff_lp = conf.pf.def_cutoff_lp;
  conf.pf.mode = conf.pf.def_mode;

	pf_app.LPfrequency = 0;
	pf_app.HPfrequency = 0;
	pf_app.FreqRatioLP = 32;
	pf_app.FreqRatioHP = 250;

	pf_app.previous_reset_state = 0;
	pf_app.current_reset_state = 0;

	HAL_GPIO_WritePin(EN_5V_GPIO_Port, EN_5V_Pin, GPIO_PIN_SET);
}


void PFHande(void)
{
  uint32_t lp_req = conf.pf.cutoff_lp;
  uint32_t hp_req = conf.pf.cutoff_hp;

  switch (conf.pf.mode)
  {
    case 0: //active low pass
      HAL_GPIO_WritePin(SW1_GPIO_Port, SW1_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(SW2_GPIO_Port, SW2_Pin, GPIO_PIN_SET);
      break;

    case 1: //active high pass filter and 100 kHz LP
      HAL_GPIO_WritePin(SW1_GPIO_Port, SW1_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SW2_GPIO_Port, SW2_Pin, GPIO_PIN_SET);
      lp_req = 100;
      break;

    case 2: //bandpass
      HAL_GPIO_WritePin(SW1_GPIO_Port, SW1_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SW2_GPIO_Port, SW2_Pin, GPIO_PIN_SET);
      break;

    default:
    case 3: //bypass both filters
      HAL_GPIO_WritePin(SW1_GPIO_Port, SW1_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(SW2_GPIO_Port, SW2_Pin, GPIO_PIN_RESET);
      break;
  }

	// high pass frequency setting
  if (hp_req != pf_app.HPfrequency)
  {
    MX_TIM_Set(TIMER_3, TIM_CHANNEL_1, hp_req * pf_app.FreqRatioHP);
    pf_app.HPfrequency = hp_req;
  }

  // low pass frequency setting
  if (lp_req != pf_app.LPfrequency)
  {
    MX_TIM_Set(TIMER_1, TIM_CHANNEL_1, lp_req * pf_app.FreqRatioLP * 1000);
    pf_app.LPfrequency = lp_req;
  }

  resetPFState();

}


// reset power supply for filters

void resetPFState(void)
{
	pf_app.current_reset_state = conf.pf.reset;

	if (pf_app.previous_reset_state == 1 && pf_app.current_reset_state == 0)
	{
		HAL_GPIO_WritePin(EN_5V_GPIO_Port, EN_5V_Pin, GPIO_PIN_RESET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(EN_5V_GPIO_Port, EN_5V_Pin, GPIO_PIN_SET);
		conf.pf.reset = 1;
	}
	pf_app.previous_reset_state = pf_app.current_reset_state;

}


