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
	switch(conf.pf.mode)
	{

	case 0: //active low pass
		HAL_GPIO_WritePin(SW1_GPIO_Port, SW1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SW2_GPIO_Port, SW2_Pin, GPIO_PIN_SET);
		break;
	case 1: //active high pass filter and 100 kHz LP

		HAL_GPIO_WritePin(SW1_GPIO_Port, SW1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SW2_GPIO_Port, SW2_Pin, GPIO_PIN_SET);
		MX_TIM_Set(TIMER_1, TIM_CHANNEL_1, 100*pf_app.FreqRatioLP*1000);

		break;
	case 2: //bandpass
		HAL_GPIO_WritePin(SW1_GPIO_Port, SW1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SW2_GPIO_Port, SW2_Pin, GPIO_PIN_SET);
		break;
	case 3: //bypass both filters
		HAL_GPIO_WritePin(SW1_GPIO_Port, SW1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SW2_GPIO_Port, SW2_Pin, GPIO_PIN_RESET);
		break;
	default:
		break;
	}



	// high pass frequency setting
	if(conf.pf.cutoff_hp != pf_app.HPfrequency)
	{
	    if (conf.pf.cutoff_hp >= 300 && conf.pf.cutoff_hp <= 10000)
	    {
	    MX_TIM_Set(TIMER_3, TIM_CHANNEL_1, conf.pf.cutoff_hp*pf_app.FreqRatioHP);
		pf_app.HPfrequency = conf.pf.cutoff_hp;
	    }
	}

	// low pass frequency setting
	if(conf.pf.cutoff_lp != pf_app.LPfrequency)
	{
		if(conf.pf.cutoff_lp >= 20 && conf.pf.cutoff_lp <= 320)
		{
		 MX_TIM_Set(TIMER_1, TIM_CHANNEL_1, conf.pf.cutoff_lp*pf_app.FreqRatioLP*1000);
		 pf_app.LPfrequency =  conf.pf.cutoff_lp;
		}

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


