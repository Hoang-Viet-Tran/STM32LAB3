/*
 * FsmTrafficLight.c
 *
 *  Created on: Dec 11, 2024
 *      Author: ADMIN
 */

#include "FsmTrafficLight.h"

int status = 0;
int timeForGreen = 5000; 	////	all times in millisecond
int timeForYellow = 3000;
int timeForRed = 8000;
int timeForGreen_tmp;
int timeForYellow_tmp;
int timeForRed_tmp;
void FsmForTrafficLight (void){
	switch (status){
	case INIT:
		status = RED1_GREEN2;
		setTimer(timeForGreen, 0);
		break;
	case RED1_GREEN2:
		value2 = timer_counter[0] * timerInterruptCycle;
		value1 = timer_counter[0] * timerInterruptCycle + timeForYellow;
		displayOn7SegLed();
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, SET);
		if(timer_flag[0] == 1){
			status = RED1_YELLOW2;
			setTimer(timeForYellow, 0);
		}
		if (isButtonPressed(0)){
			status = RED_LIGHT_CONFIG;
			clearAllLight();
			value1 = 0;
			value2 = 0;
			setTimer(500, 0);
		}
		break;
	case RED1_YELLOW2:
		value2 = timer_counter[0] * timerInterruptCycle;
		value1 = timer_counter[0] * timerInterruptCycle;
		displayOn7SegLed();
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
		if(timer_flag[0] == 1){
			status = GREEN1_RED2;
			setTimer(timeForGreen, 0);
		}
		if (isButtonPressed(0)){
			status = RED_LIGHT_CONFIG;
			clearAllLight();
			value1 = 0;
			value2 = 0;
			setTimer(500, 0);
		}
		break;
	case GREEN1_RED2:
		value2 = timer_counter[0]* timerInterruptCycle + timeForYellow;
		value1 = timer_counter[0]* timerInterruptCycle;
		displayOn7SegLed();
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
		if(timer_flag[0] == 1){
			status = YELLOW1_RED2;
			setTimer(timeForYellow, 0);
		}
		if (isButtonPressed(0)){
			status = RED_LIGHT_CONFIG;
			clearAllLight();
			value1 = 0;
			value2 = 0;
			setTimer(500, 0);
		}
		break;
	case YELLOW1_RED2:

		value2 = timer_counter[0]* timerInterruptCycle;
		value1 = timer_counter[0]* timerInterruptCycle;
		displayOn7SegLed();
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
		if(timer_flag[0] == 1){
			status = RED1_GREEN2;
			setTimer(timeForGreen, 0);
		}
		if (isButtonPressed(0)){
			status = RED_LIGHT_CONFIG;
			clearAllLight();
			value1 = 0;
			value2 = 0;
			setTimer(500, 0);
		}
		break;
	case RED_LIGHT_CONFIG:
		displayOn7SegLed();
		if(isButtonPressed(1)){
			if(value1 > 99000){
				value1 = 0;
			}else{
				value1 += 1000;
			}
		}
		if(isButtonPressed(2)){
			timeForRed_tmp = value1;
		}

		if(timer_flag[0] == 1){
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
			setTimer(500, 0);
		}
		if (isButtonPressed(0)){
			status = YELLOW_LIGHT_CONFIG;
			clearAllLight();
			value1 = 0;
			value2 = 0;
			setTimer(500, 0);
		}
		break;
	case YELLOW_LIGHT_CONFIG:
		displayOn7SegLed();
		if(isButtonPressed(1)){
			if(value1 > 99000){
				value1 = 0;
			}else{
				value1 += 1000;
			}
		}
		if(isButtonPressed(2)){
			timeForYellow_tmp = value1;
		}
		if(timer_flag[0] == 1){
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
			setTimer(500, 0);
		}
		if (isButtonPressed(0)){
			status = GREEN_LIGHT_CONFIG;
			clearAllLight();
			value1 = 0;
			value2 = 0;
			setTimer(500, 0);
		}
		break;
	case GREEN_LIGHT_CONFIG:
		displayOn7SegLed();
		if(isButtonPressed(1)){
			if(value1 > 99000){
				value1 = 0;
			}else{
				value1 += 1000;
			}
		}
		if(isButtonPressed(2)){
			timeForGreen_tmp = value1;
			if (timeForGreen_tmp + timeForYellow_tmp != timeForRed_tmp){
				status = ERROR_STATE;
				setTimer(2000, 0);
			}else{
				timeForGreen = timeForGreen_tmp;
				timeForRed = timeForRed_tmp;
				timeForYellow = timeForYellow_tmp;
			}
		}
		if(timer_flag[0] == 1){
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
			setTimer(500, 0);
		}
		if (isButtonPressed(0)){
			status = RED1_GREEN2;
			clearAllLight();
			setTimer(timeForGreen, 0);
		}
		break;
	case ERROR_STATE:
		value1 = 0;
		value2 = 0;
		displayOn7SegLed();
		turnOnAllLight();
		if(timer_flag[0]){
			status = RED1_GREEN2;
			clearAllLight();
			setTimer(timeForGreen, 0);
		}
		break;
	default:
		break;
	}
}
