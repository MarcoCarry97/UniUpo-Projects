# definizione variabili
CFLAGS=-Wall -std=c99 -g -O -pthread#Elenca tutti i parametri del compilatore
CC=gcc #nome del compilatore

#eseguibili
EXECS=forkpipe #elenca i nomi degli eseguibili che vuoi generare

forkpipe: forkpipe.o xerrors.o
	$(CC) $(CFLAGS) -o forkpipe forkpipe.o xerrors.o

forkpipe.o: forkpipe.c xerrors.h
	$(CC) $(CFLAGS) -o forkpipe.o -c forkpipe.c

xerrors.o: xerrors.c xerrors.h
	$(CC) $(CFLAGS) -o xerrors.o -c xerrors.c
