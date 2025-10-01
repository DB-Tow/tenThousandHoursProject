// utilities.c tenThousandHoursProject [tthp] Created by DBTow

#include <stdio.h>
#include <string.h>

int check_for_date(const char *date_string);

int check_for_date(const char *date_string)
{
	char *result;
	char target_character1 = '-';
	char target_character2 = '/';

	result = strchr(date_string, target_character1);
	if (result != NULL) {
		printf("Character '%c' found in a command line argument.\n", target_character1);
	}

	result = strchr(date_string, target_character2);
	if (result != NULL) {
		printf("Character '%c' found in a command line argument.\n", target_character2);
	}
	else {
		printf("There appears to be no date given in the command line argument\n");
	}

	return 0;
}
