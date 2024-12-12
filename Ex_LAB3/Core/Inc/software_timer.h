/*
 * software_timer.h
 *
 *  Created on: Dec 11, 2024
 *      Author: ADMIN
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_
#include "global.h"
extern int timer_flag[No_timers];
extern int timer_counter[No_timers];
void setTimer (int duration, int index);
void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
