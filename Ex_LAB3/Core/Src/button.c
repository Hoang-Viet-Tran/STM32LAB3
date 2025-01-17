/*
 * button.c
 *
 *  Created on: Dec 11, 2024
 *      Author: ADMIN
 */

#include "button.h"
int KeyReg0[N0_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg1[N0_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg2[N0_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg3[N0_OF_BUTTONS] = {NORMAL_STATE};


int TimeOutForKeyPress;
int TimeOutForKeyPress1 = 2000; ////	in millisecond
int timeOutforHeldKey = 250;	////	in millisecond
int button1_flag[N0_OF_BUTTONS] = {0};

void subKeyProcess(int index){
	//TODO
	button1_flag[index] = 1;
}
int isButtonPressed(int index){
	if(button1_flag[index] == 1){
		button1_flag[index] = 0;
		return 1;
	}
	return 0;
}

void getKeyInput(){
	for(int i = 0; i < 3; i ++){
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];
		//Add your button here
		KeyReg0[i] = HAL_GPIO_ReadPin(BUTTON_0_GPIO_Port, BUTTON_0_Pin<<i);

		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg2[i] != KeyReg3[i]){
			  KeyReg3[i] = KeyReg2[i];

			  if (KeyReg3[i] == PRESSED_STATE){
				TimeOutForKeyPress = TimeOutForKeyPress1/timerInterruptCycle;
				subKeyProcess(i);
			  }
			}else{
			   TimeOutForKeyPress --;
				if (TimeOutForKeyPress == 0){
					TimeOutForKeyPress =  timeOutforHeldKey/timerInterruptCycle;
					if(KeyReg3[i] == PRESSED_STATE){
						subKeyProcess(i);
					}
				}
			}
		}
	}
}
