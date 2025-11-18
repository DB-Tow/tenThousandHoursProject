// paths.c tenThousandHoursProjects tthp [Created by DBTow]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <libgen.h>
#include <unistd.h>

#include <mach-o/dyld.h> // macOS specific for: _NSGetExecutablePath()

#include "paths.h"

static char project_root[PATH_MAX];
static char db_path[PATH_MAX];
static char timer_state_path[PATH_MAX];
static int paths_initialized = 0;

int paths_init(void) {
	if (paths_initialized) {
		return 0;
	}

	char exe_path[PATH_MAX];
	uint32_t size = sizeof(exe_path);

	// Get executable path (macOS specific)
	if (_NSGetExecutablePath(exe_path, &size) != 0) {
		fprintf(stderr, "Error: Buffer too small for executable path\n");
		return -1;
	}

	// Resolve any symlinks to get the real path
	char real_path[PATH_MAX];
	if (realpath(exe_path, real_path) == NULL) {
		fprintf(stderr, "Error: Could not resolve executable path\n");
		return -1;
	}

	// Get the directory containing the executable
	char *exe_dir = dirname(real_path);
	strncpy(project_root, exe_dir, PATH_MAX - 1);
	project_root[PATH_MAX - 1] = '\0';

	// Build the database path
	snprintf(db_path, PATH_MAX, "%s/database/tthp.db", project_root);

	// Build the timer_state path
	snprintf(timer_state_path, PATH_MAX, "%s/data/timer_state", project_root);

	paths_initialized = 1;
	return 0;
}

const char* paths_get_root(void) {
	return paths_initialized ? project_root : NULL;
}

const char* paths_get_db(void) {
	return paths_initialized ? db_path : NULL;
}

const char* paths_get_timer_state(void) {
	return paths_initialized ? timer_state_path : NULL;
}
