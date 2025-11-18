tthp: src/main.c
	gcc -Iinclude src/main.c src/database.c src/parser.c  src/utilities.c src/commands.c src/timer.c src/paths.c -o tthp -lsqlite3
