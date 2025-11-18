// database.c TenThousandHoursProject [Created by DBtow]

#include <stdio.h>
#include <sqlite3.h>

#define DB_PATH "/database/tthp.db"

int db_init(void);

int db_init() {
	sqlite3 *db;
	char *err_msg = 0;

	int rc = sqlite3_open(DB_PATH, &db);
	
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Cannot open database %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		return 1;
	}
	
	// Creating main time_entries table
	const char *sql_time_entries =
		"CREATE TABLE IF NOT EXISTS time_entries ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"seconds INTEGER NOT NULL, "
		"category TEXT NOT NULL, "
		"date TEXT NOT NULL DEFAULT (DATE('now'))"
		");";

	rc = sqlite3_exec(db, sql_time_entries, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error (time entries table): %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);

		return 1;
	}

	// Creating descriptions table
	const char *sql_descriptions = 
		"CREATE TABLE IF NOT EXISTS descriptions ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"time_entry_id INTEGER NOT NULL, "
		"comment TEXT NOT NULL,"
		"FOREIGN KEY (time_entry_id) REFERENCES time_entries(id) "
		"ON DELETE CASCADE"
		");";

	rc = sqlite3_exec(db, sql_descriptions, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error (descriptions table): %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_close(db);
	return 0;
}
