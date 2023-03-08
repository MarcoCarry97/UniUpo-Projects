PROGS = error.o my_io.o my_signal.o countClient countServer 
CC = gcc -Wall
CLEANFILES = error.o my_io.o my_signal.o countServer.o countClient.o


all: ${PROGS}

error.o: error.c basic.h
	${CC} -c error.c

my_io.o:  my_io.c basic.h
	${CC} -c my_io.c

my_signal.o:  my_signal.c my_signal.h basic.h
	${CC} -c my_signal.c
	
countClient: countClient.o error.o my_io.o basic.h
	${CC} -o $@ $^

countServer: countServer.o my_signal.o error.o my_io.o basic.h
	${CC} -o $@ $^
	
clean:
	rm -f ${CLEANFILES}
	rm -f ${PROGS}
	rm -f *.*~	
	rm -f *~
