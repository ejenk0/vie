CC = gcc

vie: main
	mv main vie

main: main.o

main.o: main.c

clean:
	rm vie main.o
