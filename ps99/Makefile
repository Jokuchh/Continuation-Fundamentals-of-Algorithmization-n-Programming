# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=-lm
OUTPUT=app

# targets
all: $(OUTPUT)

$(OUTPUT): main.o track.o playlist.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) main.o track.o playlist.o  $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

track.o: track.c track.h
	$(CC) $(CFLAGS) -c track.c $(LDLIBS) -o track.o

playlist.o: playlist.c playlist.h
	$(CC) $(CFLAGS) -c playlist.c $(LDLIBS) -o playlist.o

# remove compiled files
clean:
	rm -rf $(OUTPUT) *.o
