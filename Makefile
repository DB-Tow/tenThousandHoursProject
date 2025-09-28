tthp: src/main.c
	gcc -Iinclude src/main.c src/database.c src/parser.c -o tthp -lsqlite3
