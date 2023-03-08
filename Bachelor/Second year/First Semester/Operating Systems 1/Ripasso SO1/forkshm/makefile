# definizione variabili
CFLAGS=-Wall -std=c99 -g -O -pthread#Elenca tutti i parametri del compilatore
CC=gcc #nome del compilatore

#eseguibili
EXECS=forkshm #elenca i nomi degli eseguibili che vuoi generare

forkshm: forkshm.o xerrors.o
	$(CC) $(CFLAGS) -o forkshm forkshm.o xerrors.o

forkshm.o: forkshm.c xerrors.h
	$(CC) $(CFLAGS) -o forkshm.o -c forkshm.c

xerrors.o: xerrors.c xerrors.h
	$(CC) $(CFLAGS) -o xerrors.o -c xerrors.c
