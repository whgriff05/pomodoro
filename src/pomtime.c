#include "include/pomtime.h"

void calculate_time(Time* timer) {
	char time_text[10];
	
	/* Timer is:
	   int initial_time;
	   int current_time;
	   char *text;
	*/

	int time_remaining = timer->initial_time - timer->current_time;
	int minutes_remaining = time_remaining / 60;
	int seconds_remaining = time_remaining % 60;

	sprintf(time_text, "%02d:%02d", minutes_remaining, seconds_remaining);

	free(timer->text);
	timer->text = strdup(time_text);
}

void initialize_timer(Time *timer, Pomodoro pomodoro) {
	switch(pomodoro.step) {
	case 0:
	case 1:
	case 3:
	case 5:
	case 7: {
		timer->initial_time = pomodoro.work_time;
	} break;

	case 2:
	case 4:
	case 6: {
		timer->initial_time = pomodoro.short_break_time;
	} break;

	case 8: {
		timer->initial_time = pomodoro.long_break_time;
	} break;
	}

	timer->current_time = 0;
}
