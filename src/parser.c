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
