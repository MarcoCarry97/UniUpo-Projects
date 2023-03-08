PROGS = error.o my_io.o my_signal.o my_functions.o searchClient searchServer 
CC = gcc -Wall
CLEANFILES = error.o my_io.o my_signal.o my_functions.o searchServer.o searchClient.o


all: ${PROGS}

error.o: error.c basic.h
	${CC} -c error.c

my_io.o:  my_io.c basic.h
	${CC} -c my_io.c

my_signal.o:  my_signal.c my_signal.h basic.h
	${CC} -c my_signal.c
	
my_functions.o:  my_functions.c my_functions.h basic.h
	${CC} -c my_functions.c
	
searchClient: searchClient.o error.o my_io.o my_functions.o my_functions.h basic.h
	${CC} -o $@ $^

searchServer: searchServer.o my_signal.o error.o my_io.o my_functions.o my_functions.h basic.h
	${CC} -o $@ $^
	
clean:
	rm -f ${CLEANFILES}
	rm -f ${PROGS}
	rm -f *.*~	
	rm -f *~
