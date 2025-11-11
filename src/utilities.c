// utilities.c tenThousandHoursProject [tthp] Created by DBTow

#include <stdio.h>
#include <time.h>

// Function to grab the current date and format it into a YYYY-MM-DD output string
void get_todays_date(char *output) {
	time_t now = time(NULL); // Get current time
	struct tm *t = localtime(&now); // Convert to local time
	
	sprintf(output, "%04d-%02d-%02d",
			t->tm_year + 1900, // Add 1900 to get the actual year
			t->tm_mon + 1, // Months are numbered from 0 to 11, so you add 1 to match
			t->tm_mday);
}
