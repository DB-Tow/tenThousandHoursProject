// commands.c tenThousandHoursProject tthp [Created by DBTow]

#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "parser.h"
#include "database.h"
#include "timer.h"

Command parse_command(const char *cmd_str) {
	if (!cmd_str || *cmd_str == '\0') return CMD_NONE;

	if ((strcmp(cmd_str, "log") == 0) || (strcmp(cmd_str, "Log") == 0)) return CMD_LOG;

	if ((strcmp(cmd_str, "view") == 0) || (strcmp(cmd_str, "View") == 0)) return CMD_VIEW;

	if ((strcmp(cmd_str, "timer") == 0) || (strcmp(cmd_str, "Timer") == 0)) return CMD_TIMER;

	return CMD_NONE; // Unknown command
}

// Command controller function
int execute_command(Command cmd, int argc, char **argv) {
	switch (cmd) {
		case CMD_LOG:
			return cmd_log(argc, argv);

		case CMD_TIMER:
			return cmd_timer(argc, argv);

		case CMD_VIEW:
			return cmd_view(argc, argv);

		case CMD_NONE:
		default:
			fprintf(stderr, "Error: Unknown command\n");
			return 1;
	}
}

// The function that gets executed if the "log" command is run by the user
// Parse the remaining command line arguments and inserts them into the database
// (Just printing for now)

int cmd_log(int argc, char **argv) {
	// Validate minimum arguments
	// For long the bare minimum is duration and category
	if (argc < 4) {
		fprintf(stderr, "Not enough arguments given with the log command\n");
		return 1;
	}

	TimeEntry entry = parse_log_arguments(argc, argv);

	// Check that we got a valid duration
	if (entry.seconds < 0) {
		fprintf(stderr, "Error: Valid duartion required\n");
		return 1;
	}

	// Check that we got a valid category
	if (entry.category[0] == '\0') {
		fprintf(stderr, "Error: Category is required\n");
		return 1;
	}

	printf("Duration received: %d seconds (%.1f hours)\n", entry.seconds, entry.seconds / 3600.0);
	printf("Category received: %s\n", entry.category);
	printf("Date used: %s\n", entry.date);

	if (entry.comment_count > 0) {
		printf(" Comment number: (%d)\n", entry.comment_count);
		for (int i = 0; i < entry.comment_count; i++) {
			printf(" -%s\n", entry.comments[i]);
		}
	}

	return 0;
}

// The function that gets executed if the "timer" command is run by the user
int cmd_timer(int argc, char **argv) {
	// Check for valid number of arguments
	if (argc < 3) {
		fprintf(stderr, "Error: Missing Required Arguments.\n Usage: ./tthp timer (start/stop/status/clear)\n");
		return 1;
	}

	const char *subcommand = argv[2];

	// If the clear subcommand is given
	if (strcmp(subcommand, "clear") == 0) {
		if (timer_clear_state()) {
			printf("Timer cleared.\n");
		} else {
			printf("No active timer to clear.\n");
		}
		return 0;
	}

	// Load existing state (If it exists)
	TimerState state = {false, 0, 0 };
	bool has_state = timer_read_state(&state);

	// Start / Stop Commands
	// (Functions as a toggle)
	if (strcmp(subcommand, "start") == 0) {
		// If no timer exists initialize a new timer
		if (!has_state) {
			state.is_running = true;
			state.start_time = time(NULL);
			state.accumulated_time = 0;

			timer_write_state(&state);
			printf("Timer started.\n");
			return 0;
		}

		if (state.is_running) {
			printf("A timer is currently active already.\n");
			return 0;
		}

		// This is the resume functionality
		// Or in other words stopwatch has state but is not running
		state.is_running = true;
		state.start_time = time(NULL);
		timer_write_state(&state);
		printf("Timer resumed.\n");
		return 0;
	}

	// Stop Command
	if (strcmp(subcommand, "stop") == 0) {
		if (!has_state) {
			printf("No active timer to stop.\n");
			return 0;
		}

		if (!state.is_running) {
			printf("Timer is already paused.\n");
			return 0;
		}

		time_t now = time(NULL);
		state.accumulated_time += (int)(now - state.start_time);
		state.is_running = false;
		state.start_time = 0;
		timer_write_state(&state);

		printf("Timer paused.\n");

		return 0;
	}

	if (strcmp(subcommand, "status") == 0) {
		if (!has_state) {
			printf("No active timer.\n");
			return 0;
		}

		char buf[32];
		get_elapsed_time(&state, buf, sizeof(buf));

		printf("%s\n", buf);
		fflush(stdout);
		return 0;
	}

	fprintf(stderr, "Unknown timer command: %s\n", subcommand);
	return 1;
}

int cmd_view(int argc, char **argv) {
	printf("View command received\n");
	return 0;
}
