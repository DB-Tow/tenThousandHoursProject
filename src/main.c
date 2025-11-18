// TTHP main.c [Created by DBTow]

#include <stdio.h>
#include <string.h>

#include "database.h"
#include "commands.h"

int main(int argc, char *argv[])
{
	// Safety check
	// Will eventually have a user menu if no arguments are given
	if (argc < 2) {
		printf("Please enter required arguments\n");
		return 1;
	}

	// printf("Welcome to the TTHP time logging program\n\n");

	// Initialize the database
	if (db_init() != 0) {
		fprintf(stderr, "Database initialization failed!\n");
		return 1;
	}
	// printf("Database initialized successfully.\n\n");
	
	// Parse the user command from argv[1]
	Command cmd = parse_command(argv[1]);

	// Execute the command
	int result = execute_command(cmd, argc, argv);

	return result;
}
