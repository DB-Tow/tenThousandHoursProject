// parser.c TenThousandHoursProject TTHP [Created by DBTow]

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

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
	if (year <= 2025 || year > 2100) return false;

	// Check month range (1 - 12)
	if (month < 1 || month > 12) return false;

	// First day check
	if (day < 1 || day > 31) return false;

	// Days per month array (non-leap years)
	// Starting from January at 31 days
	int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// Adjust February days per month if it is a leap year
	if (month == 2) {
		bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (is_leap) {
			days_in_month[1] = 29;
		}
	}

	// Advanced day check
	if (day > days_in_month[month - 1]) return false;
	
	return true;
}

int parse_date(const char *date_str, char *output); {
	if (!date_str || *date_str == '\0') return -1;

	int month, day, year;
	
	// Check format MM/DD/YYYY
	if (sscanf(date_str, "%d/%d/%d", &month, &day, &year) == 3) {
		if (valid_date(year, month, day)) {
			sprintf(output, "%04d-%02d-%02d", year, month, day);
			return 0;
		}
	}
	
	// Check format YYYY/MM/DD
	if (sscanf(date_str, "%d/%d/%d", &year, &month, &day) == 3) {
		if (valid_date(year, month, day)) {
			sprintf(output, "%04d-%02d-%02d", year, month, day);
			return 0;
		}
	}
	
	// Check format MM-DD-YYYY
	if (sscanf(date_str, "%d-%d-%d", &month, &day, &year) == 3) {
		if (valid_date(year, month, day)) {
			sprintf(output, "%04d-%02d-%02d", year, month, day);
			return 0;
		}
	}

	// Check format YYYY-MM-DD
	if (sscanf(date_str, "%d-%d-%d", &year, &month, &day) == 3) {
		if (valid_date(year, month, day)) {
			sprintf(output, "%04d-%02d-%02d", year, month, day);
			return 0;
		}
	}

	// No valid date format was found
	return -1;
}
