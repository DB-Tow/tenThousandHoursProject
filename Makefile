tthp: src/main.c
	gcc -Iinclude src/main.c src/database.c src/parser.c  src/utilities.c -o tthp -lsqlite3
