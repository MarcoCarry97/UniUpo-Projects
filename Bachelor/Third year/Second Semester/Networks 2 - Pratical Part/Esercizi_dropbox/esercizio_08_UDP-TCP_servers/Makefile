PROGS = error.o my_io.o my_signal.o my_functions.o Client ServerUDP ServerTCP
CC = gcc
CLEANFILES = error.o my_io.o my_signal.o my_functions.o ServerUDP.o ServerTCP.o Client.o


all: ${PROGS}

error.o: error.c basic.h
	${CC} -c error.c

my_io.o:  my_io.c basic.h
	${CC} -c my_io.c

my_signal.o:  my_signal.c my_signal.h basic.h
	${CC} -c my_signal.c
	
my_functions.o:  my_functions.c my_functions.h basic.h
	${CC} -c my_functions.c
	
Client: Client.o error.o my_io.o my_functions.o my_functions.h basic.h
	${CC} -o $@ $^

ServerUDP: ServerUDP.o my_signal.o error.o my_io.o my_functions.o my_functions.h basic.h
	${CC} -o $@ $^

ServerTCP: ServerTCP.o my_signal.o error.o my_io.o my_functions.o my_functions.h basic.h
	${CC} -o $@ $^
	
clean:
	rm -f ${CLEANFILES}
	rm -f ${PROGS}
	rm -f *.*~	
	rm -f *~
