// parser.c TenThousandHoursProject TTHP [Created by DBTow]

#include <stdio.h>

int parse_time(const char *time_str);

int parse_time(const char *time_str)
{
	int hours;
	int minutes;

	int result = sscanf(time_str, "%dh %dm", &hours, &minutes);

	int total_seconds = (hours * 3600) + (minutes * 60);

	return total_seconds;
}

