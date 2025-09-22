// TTHP main.c [Created by DBTow]

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	printf("Welcome to the TTHP time logging program\n");
	printf("\n");

	int i;
	char *commands[] = { "log" };
	
	printf("Number of arguments: %d\n", argc);
	for (i = 0; i < argc; i++)
		printf("Argv[%d]: %s\n", i, argv[i]);
	if (strcmp(argv[1], commands[0]) == 0) {
		printf("Log command recognized\n");
	}

	return 0;
}
