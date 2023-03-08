CC= gcc
FLAGS= -Wall -std=c99 -g -O -pthread
EXEC=sumpipe

all: $(EXEC)

sumpipe: sumpipe.o xerrors.o
	$(CC) $(FLAGS) -o sumpipe sumpipe.o xerrors.o

sumpipe.o: sumpipe.c xerrors.h
	$(CC) $(FLAGS) -o sumpipe.o -c sumpipe.c

xerrors.o: xerrors.c xerrors.h
	$(CC) $(FLAGS) -o xerrors.o -c xerrors.c
