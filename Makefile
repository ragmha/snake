# makefile for Snake

CC = gcc
DEBUG = -g
CFLAGS  := -Wall $(DEBUG)
LIBS  := -lcurses
SOURCES := main.c
OBJS := game.o menus.o main.o
EXE := Snake

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE) $(LIBS)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

menus.o: menus.c menus.h
	$(CC) $(CFLAGS) -c menus.c

run: $(EXE)
	./$(EXE)

clean:
	rm -f *.o $(EXE) *.stackdump
