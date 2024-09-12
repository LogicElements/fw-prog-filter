/*
 * TIMER.h
 *
 *  Created on: Aug 29, 2024
 *      Author: evzen
 */

#ifndef BOARD_TIMER_H_
#define BOARD_TIMER_H_


typedef enum {
    TIMER_1,
    TIMER_2,
    TIMER_3
} TimerEnum;


void MX_TIM_Set(TimerEnum timer, uint32_t channel, uint32_t frequency);

#endif /* BOARD_TIMER_H_ */
