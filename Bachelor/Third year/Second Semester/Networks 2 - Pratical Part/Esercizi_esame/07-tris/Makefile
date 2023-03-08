PROGS = error.o my_io.o my_signal.o my_functions.o client server 
CC = gcc -Wall
CLEANFILES = error.o my_io.o my_signal.o my_functions.o server.o client.o


all: ${PROGS}

error.o: error.c basic.h
	${CC} -c error.c

my_io.o:  my_io.c basic.h
	${CC} -c my_io.c

my_signal.o:  my_signal.c my_signal.h basic.h
	${CC} -c my_signal.c
	
my_functions.o:  my_functions.c my_functions.h basic.h
	${CC} -c my_functions.c
	
client: client.o error.o my_io.o my_functions.o my_functions.h basic.h
	${CC} -o $@ $^

server: server.o my_signal.o error.o my_io.o my_functions.o my_functions.h basic.h
	${CC} -o $@ $^
	
clean:
	rm -f ${CLEANFILES}
	rm -f ${PROGS}
	rm -f *.*~	
	rm -f *~
