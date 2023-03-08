# makefile che utilizza regole implicite e variabili
#
# usare 
#    make <nome_eseguibile> 
# per compilare un unico programma, o semplicemente
#    make
# per compilarli tutti 
#
CFLAGS=-Wall -std=c99 -g -O
CC=gcc

# eseguibili da creare
EXECS= giococarte


all: $(EXECS)


giococarte: giococarte.o structure.o
	$(CC) $(CFLAGS) -o giococarte giococarte.o structure.o

# regola per contapar.o che usa anche la dipendenza da xerrors.h
giococarte.o: giococarte.c structure.h
	$(CC) $(CFLAGS) -c giococarte.c -o giococarte.o


clean:
	rm *.o $(EXECS)

