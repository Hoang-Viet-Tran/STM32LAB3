/*
 * software_timer.c
 *
 *  Created on: Dec 11, 2024
 *      Author: ADMIN
 */

#include "software_timer.h"
#include "global.h"

int timer_flag[No_timers] = {};
int timer_counter[No_timers] ={};
void setTimer (int duration, int index){	// duration is time value want to set in millisecond
	timer_counter[index] = duration / timerInterruptCycle;
	timer_flag[index] = 0;
}
void timer_run (){
	for(int i = 0;i < No_timers; i++){
		if( timer_counter[i] > 0){
			timer_counter[i] --;
		if( timer_counter[i] == 0) timer_flag[i] = 1;
		}
	}

}
