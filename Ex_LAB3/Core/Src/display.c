/*
 * display.c
 *
 *  Created on: Dec 11, 2024
 *      Author: ADMIN
 */

#include "display.h"
#include "main.h"
#include "global.h"
unsigned char NUM[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
void display7SEG (int number){
	GPIOB -> ODR = NUM[number];
}
int value1 = 100;
int value2 = 100;
int index_led = 0;
int led_buffer [4] = {5,6,7,8};
 void update7SEG (int index){
	switch (index){
	case 0:
		// Display the first 7 SEG with led_buffer [0]

		HAL_GPIO_WritePin(EN_0_GPIO_Port, EN_0_Pin, RESET);
		HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, SET);
		HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, SET);
		HAL_GPIO_WritePin(EN_3_GPIO_Port, EN_3_Pin, SET);
		display7SEG(led_buffer[0]);
		break ;
	case 1:
		// Display the second 7 SEG with led_buffer [1]

		HAL_GPIO_WritePin(EN_0_GPIO_Port, EN_0_Pin, SET);
		HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, RESET);
		HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, SET);
		HAL_GPIO_WritePin(EN_3_GPIO_Port, EN_3_Pin, SET);
		display7SEG(led_buffer[1]);
		break ;
	case 2:
		// Display the third 7 SEG with led_buffer [2]

		HAL_GPIO_WritePin(EN_0_GPIO_Port, EN_0_Pin, SET);
		HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, SET);
		HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, RESET);
		HAL_GPIO_WritePin(EN_3_GPIO_Port, EN_3_Pin, SET);
		display7SEG(led_buffer[2]);

		break ;
	case 3:
		// Display the forth 7 SEG with led_buffer [3]

		HAL_GPIO_WritePin(EN_0_GPIO_Port, EN_0_Pin, SET);
		HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, SET);
		HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, SET);
		HAL_GPIO_WritePin(EN_3_GPIO_Port, EN_3_Pin, RESET);
		display7SEG(led_buffer[3]);
		break ;
	default :
		break ;
	}
}
void update7SegBuffer(){
//	value1 = timer_counter[0];
	led_buffer[0] = value1/10000;
	led_buffer[1] = (value1%10000)/1000;
	led_buffer[2] = value2/10000;
	led_buffer[3] = (value2%10000)/1000;
}
void displayOn7SegLed(){
	update7SegBuffer();
	if(timer_flag[1] == 1){
		  if (index_led > 3){
			index_led = 0;
		  }update7SEG(index_led++);
		  setTimer(50, 1);
	  }
}
void clearAllLight(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
}
void turnOnAllLight(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, SET);
}
