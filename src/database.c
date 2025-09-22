// database.c TenThousandHoursProject [Created by DBtow]

#include <stdio.h>
#include <sqlite3.h>

#define DB_PATH "./database/tthp.db"

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
	
	char *sql =
		"CREATE TABLE IF NOT EXISTS time_entries ("
		"id INTEGER PRIMARY KEY, "
		"seconds INTEGER, "
		"category TEXT, "
		"description TEXT"
		");";

	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);

		return 1;
	}
	
	sqlite3_close(db);
	return 0;
}
