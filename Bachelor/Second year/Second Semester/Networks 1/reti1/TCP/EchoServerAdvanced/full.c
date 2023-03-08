#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include"full.h"

/*ssize_t fullWrite(int fd,const void *buf,size_t count) //SCRITTURA FULL
{
	size_t left=count;
	ssize_t written;
	while(left>0)
	{
		written=write(fd,buf,left);
		if(written<0)
			if(errno!=EINTR)
				return written;
		left-=written;
		buf+=written;
	}
	return left;
}

ssize_t fullRead(int fd, void *buf, size_t count) //LETTURA FULL
{
	size_t left=count;
	ssize_t nread;
	bool end=false;
	while(left>0 && !end)
	{
		nread=read(fd,buf,left);
		if(nread<0)
			if(errno!=EINTR)
				return nread;
		if(nread==0) end=true;
		left-=nread;
		buf+=nread;
	}
	return left;
}*/

int xsocket(int typeAddress, int typePort, int protocol) //CREA UN SOCKET
{
	int sock=socket(typeAddress,typePort,protocol);
	if(sock==-1)
	{
		fprintf(stderr,"Could not create a socket\n");
		exit(0);
	}
	else
	{
		fprintf(stderr,"Socket created\n");
		return sock;
	}
}

int xbind(int socket, const struct sockaddr_in *address,socklen_t length) //ESEGUE IL BIND
{
	int ret=bind(socket,(struct sockaddr *)address,length);
	if(ret==0)
	{
		fprintf(stderr,"Bind Completed\n");
		return ret;
	}
	else
	{
		fprintf(stderr,"Could not bind to address\n");
		close(socket);
		exit(0);
	}
}

int xconnect(int socket,const struct sockaddr_in *address,socklen_t length) //TENTA UNA CONNESSIONE AL SERVER
{
	int ret=connect(socket,(struct sockaddr *)address,length);
	if(ret==0)
	{
		fprintf(stderr,"Connect successful\n");
		return ret;
	}
	else
	{
		fprintf(stderr, "Could not connect to address!\n");
		close(socket);
		exit(1);
	}
}

int xlisten(int socket,int backlog) //RIMANE IN ASCOLTO DI UN CLIENT
{
	int ret=listen(socket,backlog);
	if(ret==-1)
	{
		fprintf(stderr,"Cannot listen on socket!\n");
		close(socket);
		exit(1);
	}
	else return ret;
}

int xaccept(int socket,struct sockaddr_in *restrict address, socklen_t *restrict length) //ACCETTA LA CONNESSIONE EFFETTUATA
{
	int ret=accept(socket,(struct sockaddr *) address,length);
	if(ret==-1)
	{
		fprintf(stderr, "Cannot accept connections!\n");
	    	close(socket);
	    	exit(1);
	}
	else return ret;
}

size_t xwrite(int fd,void *buf, size_t bytes) //SCRITTURA
{
	int ret=write(fd,buf,bytes);
	if(ret<=0)
	{
		fprintf(stderr, "Return Status = %d \n", ret);
		exit(0);
	}
	else return ret;
}

size_t xread(int fd,void *buf, size_t bytes) //LETTURA
{
	int ret=read(fd,buf,bytes);
	if(ret<=0)
	{
		fprintf(stderr, "Return Status = %d \n", ret);
		exit(0);
	}
	else return ret;
}

int xclose(int fd) //CHIUSURA
{
	int ret=close(fd);
	if(ret==-1) exit(0);
	else return ret;
}
