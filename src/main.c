// TTHP main.c [Created by DBTow]

#include <stdio.h>
#include <string.h>

#include "database.h"
#include "parser.h"

int main(int argc, char *argv[])
{
	printf("Welcome to the TTHP time logging program\n");
	printf("\n");

	if (db_init() != 0) {
		fprintf(stderr, "Database initialization failed!\n");
		return 1;
	}
	printf("Database initialized successfully.\n\n");

	int i;
	char *commands[] = { "log" };
	
	printf("Number of arguments: %d\n", argc);
	for (i = 0; i < argc; i++)
		printf("Argv[%d]: %s\n", i, argv[i]);
	if (strcmp(argv[1], commands[0]) == 0) {
		printf("Log command recognized\n");
		int result = parse_time(argv[2]);
		printf("Parsed %d seconds from '%s'\n", result, argv[2]);
	}

	return 0;
}
