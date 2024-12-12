/*
 * global.h
 *
 *  Created on: Dec 11, 2024
 *      Author: ADMIN
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#define No_timers 2
#define prescaler 7999
#define counter 9
extern int timer_flag[No_timers];
extern int timer_counter[No_timers];
extern int timerInterruptCycle;
extern int status;
#include "main.h"
#include "software_timer.h"
#include "display.h"
#include "FsmTrafficLight.h"
#include "button.h"


#endif /* INC_GLOBAL_H_ */
