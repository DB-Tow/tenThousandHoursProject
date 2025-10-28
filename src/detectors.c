// detectors.c tenThoushandHoursProject [Created by DBTow]

#include <stdbool.h>
#include <ctype.h>

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
