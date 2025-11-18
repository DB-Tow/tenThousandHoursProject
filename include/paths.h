// paths.h tenThousandHoursProject tthp [Created by DBTow]

#ifndef PATHS_H
#define PATHS_H

// Initialize the path system... Called once at program start
// Returns 0 on succes, -1 on failure
int paths_init(void);

// Fetches the project root directory (Where the tthp executable is located)
const char* paths_get_root(void);

// Get the full path to the database file
const char* paths_get_db(void);

// Get the full path to the timer_state file
const char* paths_get_timer_state(void);

#endif
