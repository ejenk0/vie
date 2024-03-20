CC = gcc
CFLAGS = -lncurses
DEBUGFLAGS = -g3

vie: main
	mv $< $@

debug: main.c
	$(CC) $< -o $@ $(CFLAGS) $(DEBUGFLAGS)

main: main.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -f vie debug
