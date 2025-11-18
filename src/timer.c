// timer.c tenThousandHoursProject tthp [Created by DBTow]

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "timer.h"
#include "paths.h"

bool timer_read_state(TimerState *state) {
	// Build the path to the /data/timer_state file
	const char *timer_state_path = paths_get_timer_state();

	FILE *fp = fopen(timer_state_path, "r");
	if (!fp) {
		return false; // File doesn't exist
	}

	int running;
	long start, accumulated;

	int n = fscanf(fp, "%d %ld %ld", &running, &start, &accumulated);
	fclose(fp);

	if (n != 3) return false;

	state->is_running = (running == 1);
	state->start_time = (time_t)start;
	state->accumulated_time = (int)accumulated;

	return true;
}

bool timer_write_state(const TimerState *state) {
	const char *timer_state_path = paths_get_timer_state();

	FILE *fp = fopen(timer_state_path, "w");
	if (!fp) {
		return false;
	}

	fprintf(fp, "%d %ld %d\n",
			state->is_running ? 1 : 0,
			(long)state->start_time,
			state->accumulated_time
		);


	fclose(fp);
	return true;
}

bool timer_clear_state() {
	const char *timer_state_path = paths_get_timer_state();
	if (!timer_state_path) {
		return false;
	}
	return unlink(timer_state_path) == 0;
}

int get_elapsed_time(const TimerState *state, char *buf, size_t len) {
	time_t now = time(NULL);
	int total = state->accumulated_time;

	if (state->is_running) {
		total += (int)(now - state->start_time);
	}

	int hours = total / 3600;
	int minutes = (total % 3600) / 60;
	int seconds = total % 60;

	return snprintf(buf, len, "%02d:%02d:%02d", hours, minutes, seconds);
}
