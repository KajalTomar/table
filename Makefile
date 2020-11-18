main: table.h table.c main.c
	clang -Wall main.c table.o -o main

table.o: table.h table.c
	clang -Wall -c table.c -o table.o

clean:
	rm table.o main.o main
