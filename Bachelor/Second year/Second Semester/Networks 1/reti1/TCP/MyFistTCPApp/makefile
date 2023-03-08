CC=gcc
FLAGS= -Wall -std=c99 -g -O
EXEC= client server
all:$(EXEC)
client: client.o full.o
	$(CC) $(FLAGS) -o client client.o full.o
client.o: client.c full.h
	$(CC) $(FLAGS) -o client.o -c client.c
server: server.o full.o
	$(CC) $(FLAGS) -o server server.o full.o
server.o: server.c full.h
	$(CC) $(FLAGS) -o server.o -c server.c
full.o: full.c full.h
	$(CC) $(FLAGS) -o full.o -c full.c
