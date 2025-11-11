// parser.h TenThousandHoursProject TTHP [Created by DBTow]

#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

typedef struct {
	int seconds;
	char date[11];
	char category[256];
	char *comments[10];
	int comment_count;
} TimeEntry;

int parse_time(const char *time_str);

bool valid_date(int year, int month, int day);

int parse_date(const char *date_str, char *output);

TimeEntry parse_log_arguments(int argc, char **argv);


#endif
