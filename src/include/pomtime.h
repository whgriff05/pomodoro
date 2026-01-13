#ifndef POMTIME_H
#define POMTIME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"


typedef struct {
	int initial_time;
	int current_time;
	char *text;
} Time;

typedef struct {
	int work_time;
	int short_break_time;
	int long_break_time;
	int step;
	/* Steps for Timer
	   0 - Before a pomodoro has started
	   1 - Work 1
	   2 - Short Break 1
	   3 - Work 2
	   4 - Short Break 2
	   5 - Work 3
	   6 - Short Break 3
	   7 - Work 4
	   8 - Long Break

	   Steps for Settings
	   0 - Work time
	   1 - Short Break Time
	   2 - Long Break Time
	*/
} Pomodoro;

void calculate_time(Time* timer);
void initialize_timer(Time *timer, Pomodoro pomodoro);


#endif
