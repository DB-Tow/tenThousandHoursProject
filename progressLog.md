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

(09/28/2025)
-Began working on the parsing logic of the command line arguments
-Created parse.c / parser.h files

-In parser.c I created the function parse_time() that takes a pointer to a constant character array. This character array will be coming from the command line argument.

-parse_time takes a string in the format "Xh Ym" (For example: "2h 30m") and extracts the hours and minutes and assigns them to variables using the sscanf function.
It then converts the two into their respective seconds equivalent and adds them together in a variable: total_seconds

This is the value that is returned by the function. The parser.h file was updated to make this parse_time function globally available. The makefile was also updated appropriately.

In main.c after the log command has been recognized it runs the parse_time function on argv[2] it then stores the result of the time calculation in a variable called result. For the time being result is then just simply printed.


I am acutely aware of the downsides to hardcoding user input at specific argv[i] locations. For right now it will operate on a strict user input format because it will just be me using it but in the future I will make it more robust and
add more sophiscated error checking. Right now just trying to get a working product that I can use for my personal development and then tweak later on with different versions.

For right now the working format for running the program should look something like: ./tthp log 1h30m CompSci "Studied Unix" "Studied C"
    -Need to think of a date solution as well (want to have default behavior be take the current date time-stamp but also offer the ability to add data in retroactively)

After writing and committing the time parsing aspect I worked on the other two portions of the data entry: category and description/comments

-I hard coded the argv[3] to be assigned to the character string category. That character string is printed back for error checking.

-Now to deal with the description. First we declare a fixed-size array to hold the single discription string. We then set the first element of the array to '\0'. (Which initializes it as an empty C-string).

We then iterate again over the command line arguments starting at index 4 (strict format version) and anything at or over argv[4] is treated as comment for the description string and using the strcat() function its concatenated to the
description string.
    -Each comment is further separated by a newline character that is concatenated to the description string in the same loop.


(Checkpoint)
I think I need to change my data heirarchy scheme a little:
-First and foremost I'm thinking of creating a second schema calling it description and having it link to the time logs table via foreign key.
-Second I want to add the ability to log current or retroactive dates to time_logs (completely overlooked this important aspect)

Having a date attached to time log entries will be essential for time querying operations I imagine. Especially when I begin working on building reporting features for the program.


