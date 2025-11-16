// parser.c TenThousandHoursProject TTHP [Created by DBTow]

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "parser.h"
#include "utilities.h" // header for get_todays_date function

int parse_time(const char *time_str) {
	if (!time_str || *time_str == '\0') return -1;

	const char *p = time_str;
	bool h_exists = false, m_exists = false, s_exists = false;
	int total_seconds = 0;
	int current_num = 0;

	while(*p != '\0') {
		if (!isdigit((unsigned char)*p)) return -1;

		while (isdigit((unsigned char)*p)) {
			// Character to digit conversion
			current_num = (current_num * 10) + (*p - '0');
			p++;
		}

		if (*p == 'h') {
			if (h_exists) return -1; // Duplicate prevention
			h_exists = true;
			total_seconds = total_seconds + (current_num * 3600);
			current_num = 0;
			p++;
		}

		else if (*p == 'm') {
			if (m_exists) return -1;
			m_exists = true;
			total_seconds = total_seconds + (current_num * 60);
			current_num = 0;
			p++;
		}

		else if (*p == 's') {
			if (s_exists) return -1;
			s_exists = true;
			total_seconds = total_seconds + current_num;
			current_num = 0;
			p++;
		}

		else {
			return -1; // Error
		}
	}

	return total_seconds;
}

bool valid_date(int year, int month, int day) {
	// Check year range
	// Acceptable years are from 2025 to 2100
	if (year < 2025 || year > 2100) return false;

	// Check month range (1 - 12)
	if (month < 1 || month > 12) return false;

	// Days per month array (non-leap years)
	// days_per_month[0] = January at 31 days
	int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// Adjust February days per month if it is a leap year
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		days_per_month[1] = 29;
	}

	// Check the day range (checks per month) 
	if (day < 1 || day > days_per_month[month - 1]) return false;
	
	return true;
}

int parse_date(const char *date_str, char *output) {
	if (!date_str || *date_str == '\0') return -1;

	int month, day, year;
	int first, second, third;
	
	// Check format MM/DD/YYYY or YYYY/MM/DD (slash separator)
	if (sscanf(date_str, "%d/%d/%d", &first, &second, &third) == 3) {

		// Determine format based on the first number
		if (first > 31) {
			// Indicates YYYY/MM/DD format
			year = first;
			month = second;
			day = third;
		} else {
			// Indicates MM/DD/YYYY format
			month = first;
			day = second;
			year = third;
		}

		if (valid_date(year, month, day)) {
			sprintf(output, "%04d-%02d-%02d", year, month, day);
			return 0;
		}
		return -2; // Date format recognized but an invalid date was given
	}

	//Check format MM-DD-YYYY or YYYY-MM-DD (dash separator)
	if (sscanf(date_str, "%d-%d-%d", &first, &second, &third) == 3) {
		if (first > 31) {
			year = first;
			month = second;
			day = third;
		} else {
			month = first;
			day = second;
			year = third;
		}

		if (valid_date(year, month, day)) {
			sprintf(output, "%04d-%02d-%02d", year, month, day);
			return 0;
		}
		return -2; 
	}
	
	// No valid date format was found
	return -1;
}

TimeEntry parse_log_arguments(int argc, char **argv) {
	TimeEntry entry;

	// Initialize the struct with "empty" values
	entry.seconds = -1;
	entry.date[0] = '\0';
	entry.category[0] = '\0';
	entry.comment_count = 0;

	bool found_category = false;

	// Loop through all user given arguments
	// Excludes argv[0] (which is the program name) and argv[1] (which will always be a user command like "log")
	for (int i = 2; i < argc; i++) {
		
		// Checking for a valid time duration
		int valid_time = parse_time(argv[i]);
		if (valid_time > 0) {
			entry.seconds = valid_time;
			continue; // Move to the next argument
		}

		// Checking for a valid date format
		char date_buffer[11];
		int date_result = parse_date(argv[i], date_buffer);
		if (date_result == 0) {
			strcpy(entry.date, date_buffer);
			continue;
		} else if (date_result == -2) {
			// Date format was recognized but an invalid date was given
			fprintf(stderr, "Error: Date format recognized but invalid date given '%s'. Please use a valid date between 2025-2100.\n", argv[i]);
			entry.seconds = -1; // Mark entry as invalid
			return entry;
		}

		// Check for category (category = first non duration or date argument)
		if (!found_category) {
			strncpy(entry.category, argv[i], sizeof(entry.category) - 1);
			entry.category[sizeof(entry.category) - 1] = '\0'; // Null terminating the string
			found_category = true;
		} else {
			if (entry.comment_count < 10) {
				entry.comments[entry.comment_count++] = argv[i];
			} else {
				fprintf(stderr, "Error: Maximum comment count is 10");
			}
		}
	}

	// If no date is given default behavior is use the current date 
	if (entry.date[0] == '\0') {
		get_todays_date(entry.date); // Function that grabs the current date [from utilities.c]
	}

	return entry;
}
