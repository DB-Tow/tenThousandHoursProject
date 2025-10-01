// TTHP main.c [Created by DBTow]

#include <stdio.h>
#include <string.h>

#include "database.h"
#include "parser.h"
#include "utilities.h"

int main(int argc, char *argv[])
{
	// Safety check
	// Will eventually have a user menu if no arguments are given
	if (argc < 2) {
		printf("Please enter required arguments\n");
		return 1;
	}

	printf("Welcome to the TTHP time logging program\n\n");

	if (db_init() != 0) {
		fprintf(stderr, "Database initialization failed!\n");
		return 1;
	}
	printf("Database initialized successfully.\n\n");

	int i;
	char *commands[] = { "log" };

	if (strcmp(argv[1], commands[0]) == 0) {
		printf("Log command recognized\n");

		for (i = 2; i < argc; i++) {
			check_for_date(argv[i]);
		}

		int seconds_duration = parse_time(argv[2]);

		printf("Parsed %d seconds from '%s'\n", seconds_duration, argv[2]);

		char *category = argv[3];
		printf("The category you have selected is: %s\n", category);

		// Build description string
		char description[256];
		description[0] = '\0';

		for (i = 4; i < argc; i++) {
			strcat(description, argv[i]);
			strcat(description, "\n");
	}
		printf("Description: %s\n", description);
	}
	return 0;
}
