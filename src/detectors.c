// detectors.c tenThoushandHoursProject [Created by DBTow]

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

// Function designed to detect if a valid time duration exists from the user input.
// Valid time is <amount of time><unit of time>
// For example: 1h20m
// This would represent 1 hour and 20 minutes of time
bool is_duration(const char *str) {
	if (!str || *str == '\0') return false;

	const char *p = str;
	bool h_exists = false, m_exists = false, s_exists = false;
	bool valid_duration_exists = false;

	while (*p != '\0') {
		if (!isdigit((unsigned char)*p)) return false;

		while (isdigit((unsigned char)*p)) p++;

		if (*p == 'h') {
			if (h_exists) return false; // Duplicate prevention
			h_exists = true;
			valid_duration_exists = true;
			p++;
		}
		else if (*p == 'm') {
			if (m_exists) return false;
			m_exists = true;
			valid_duration_exists = true;
			p++;
		}
		else if (*p == 's') {
			if (s_exists) return false;
			s_exists = true;
			valid_duration_exists = true;
			p++;
		}
		else {
			return false; // Unexpected character 
		}
	}

	return valid_duration_exists;
}

// Function designed to detect if a valid date exists from the user input.
// Function returns true or false. True being a valid date was detected / false being did not pass the detector test.
// Valid date format include: MM/DD/YYYY MM-DD-YYYY or YYYY/MM/DD YYYY-MM-DD
// MM DD YYYY represent month day and year respectively.
bool is_date(const char *str) {
	if (!str || *str == '\0') return false;

	int month, day, year;

	// Check MM/DD/YYYY format
	if (sscanf(str, "%d/%d/%d", &month, &day, &year) == 3) {
		if (year >= 1900 && year <= 2100 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
			return true;
		}
	}

	// Check MM-DD-YYYY format
	if (sscanf(str, "%d-%d-%d", &month, &day, &year) == 3) {
		if (year >= 1900 && year <= 2100 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
			return true;
		}
	}

	// Check YYYY/MM/DD format
	if (sscanf(str, "%d/%d/%d", &year, &month, &day) == 3) {
		if (year >= 1900 && year <= 2100 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
			return true;
		}	
	}

	// Check YYYY-MM-DD format
	if (sscanf(str, "%d-%d-%d", &year, &month, &day) == 3) {
		if (year >= 1900 && year <= 2100 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
			return true;
		}
	}

	return false;
}
