PROGS = directory_server server client
# options used for debugging -Wall -ggdb
CC = gcc -Wall
MYSQL = `mysql_config --cflags --libs`
CLEANFILES = error.o my_io.o my_signal.o list.o my_functions.o mysql.o directory_server.o server.o client.o


all: ${PROGS}

error.o: error.c basic.h
	${CC} -c error.c

my_io.o:  my_io.c basic.h
	${CC} -c my_io.c

my_signal.o:  my_signal.c my_signal.h basic.h
	${CC} -c my_signal.c
	
list.o: list.c list.h
	${CC} -c list.c

mysql.o: mysql.c basic.h mysql.h
	${CC} ${MYSQL} -c mysql.c 

my_functions.o: my_functions.c my_functions.h
	${CC} -c my_functions.c
	
directory_server: directory_server.o my_functions.o mysql.o error.o my_io.o list.o basic.h
	${CC} -o $@ $^ ${MYSQL}
	
server: my_functions.o server.o my_signal.o mysql.o error.o basic.h
	${CC} -o $@ $^ ${MYSQL}

client: my_functions.o error.o client.o basic.h
	${CC} -o $@ $^
	
clean:
	rm -f ${CLEANFILES}
	rm -f ${PROGS}
	rm -f *.*~	
	rm -f *~
