CC = gcc

vie: main
	mv main vie

debug: main.c
	gcc main.c -o dvie -g3

main: main.o

main.o: main.c

clean:
	rm vie main.o
