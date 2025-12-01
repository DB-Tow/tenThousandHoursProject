// database.c TenThousandHoursProject [Created by DBtow]

#include <stdio.h>
#include <sqlite3.h>

#include "paths.h"


int db_init(void);

int db_init() {
	// Build the database path
	const char *db_path = paths_get_db();

	sqlite3 *db;
	char *err_msg = 0;

	int rc = sqlite3_open(db_path, &db);
	
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Cannot open database %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		return 1;
	}

	// Enable foreign key support
	sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, 0);

	// Creating projects table
	const char *sql_projects =
		"CREATE TABLE IF NOT EXISTS projects ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"name TEXT UNIQUE NOT NULL"
		");";

	rc = sqlite3_exec(db, sql_projects, 0, 0, &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error (projects table): %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);
		
		return 1;
	}
	
	// Creating main time_entries table
	const char *sql_time_entries =
		"CREATE TABLE IF NOT EXISTS time_entries ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"seconds INTEGER NOT NULL, "
		"category TEXT NOT NULL, "
		"date TEXT NOT NULL DEFAULT (DATE('now')), "
		"project_id INTEGER, "
		"FOREIGN KEY (project_id) REFERENCES projects(id)"
		");";

	rc = sqlite3_exec(db, sql_time_entries, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error (time entries table): %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);

		return 1;
	}

	// Creating comments table
	const char *sql_comments = 
		"CREATE TABLE IF NOT EXISTS comments ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"time_entry_id INTEGER NOT NULL, "
		"comment TEXT NOT NULL,"
		"FOREIGN KEY (time_entry_id) REFERENCES time_entries(id) "
		"ON DELETE CASCADE"
		");";

	rc = sqlite3_exec(db, sql_comments, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error (comments table): %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_close(db);
	return 0;
}
