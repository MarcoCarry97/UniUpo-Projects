# definizione variabili
CFLAGS=-Wall -std=c99 -g -O -pthread#Elenca tutti i parametri del compilatore
CC=gcc #nome del compilatore

#eseguibili
EXECS=maxthread #elenca i nomi degli eseguibili che vuoi generare

maxthread: maxthread.o xerrors.o
	$(CC) $(CFLAGS) -o maxthread maxthread.o xerrors.o

maxthread.o: maxthread.c xerrors.h
	$(CC) $(CFLAGS) -o maxthread.o -c maxthread.c

xerrors.o: xerrors.c xerrors.h
	$(CC) $(CFLAGS) -o xerrors.o -c xerrors.c
