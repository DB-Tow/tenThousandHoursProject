// commands.c tenThousandHoursProject tthp [Created by DBTow]

#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "parser.h"
#include "database.h"

Command parse_command(const char *cmd_str) {
	if (!cmd_str || *cmd_str == '\0') return CMD_NONE;

	if ((strcmp(cmd_str, "log") == 0) || (strcmp(cmd_str, "Log") == 0)) return CMD_LOG;

	if ((strcmp(cmd_str, "view") == 0) || (strcmp(cmd_str, "View") == 0)) return CMD_VIEW;

	return CMD_NONE; // Unknown command
}

// Command controller function
int execute_command(Command cmd, int argc, char **argv) {
	switch (cmd) {
		case CMD_LOG:
			return cmd_log(argc, argv);

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

int cmd_view(int argc, char **argv) {
	printf("View command received\n");
	return 0;
}
