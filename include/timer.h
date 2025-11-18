// timer.h tenThousandHoursProject tthp [Created by DBTow]

#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <stdbool.h> 


// Timer state struct
typedef struct {
	bool is_running; 		// 1 = running and 0 = not running
	time_t start_time; 		// A Unix timestamp of when the timer was last started
	int accumulated_time; 		// The amount of accumulated time counted
} TimerState;

// Function declarations

bool timer_read_state(TimerState *state);

bool timer_write_state(const TimerState *state);

bool timer_clear_state();

int get_elapsed_time(const TimerState *state, char *buf, size_t len);

#endif
