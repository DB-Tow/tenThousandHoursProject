# TenThousandHoursProject (TTHP) Progress Log [Created by DBTow]

(08/24/2025)
-Initialized the project on Github
-Created a basic README.md and .gitignore

(09/22/2025)
-Created this here progress log

-Introduced more project structure by creating src/ and include/ files
-In src/ created a main.c (This will serve as the entry point of the program)

-Created a very basic Makefile (my first ever!)
    -Spent a small amount of time learning how to make / use a Makefile

-Learned how to access command line arguments
    -argc and argv
    -In main.c adjusted the main function to print a couple of things: Number of command line arguments / Each string in accordance with its argv[] position
        -Also added a separate print message that checks if argv[1] == "log" to represent the log command
        -This is how we will receive and process user input

-Reviewed C/SQLITE API documentation and watched some youtube videos on the topic.

-In src/ created a database.c
    -Inside this file created a function db_init() that opens a database at the defined path ./database/ or creates if it does not exist.
    -Then after the initial database file has been created or opened a SQL table is created and inserted (if it doesn't exist)

Our schema is a table named time_entries that has an id / seconds / category / description.
    -The id will be the primary key identifier
    -Seconds will be the total amount of time in seconds that was spent on an activity to be logged.
    -Category will be a text option for what field of discpline the time should be logged to.
    -Description will be a series of comments describing what the logged time was spent on.

The SQL table is inserted using the sqlite3_exec() interface. If all these operations were performed successfully it closes the database and returns 0.

-Created a database.h header that makes the db_init() function globablly available. Also updated the makefile to add the ./include directory to header search path.

-In main.c after linking the header file I called the function db_init() and upon success it will print a message to the user that the database was successfully initialized.


