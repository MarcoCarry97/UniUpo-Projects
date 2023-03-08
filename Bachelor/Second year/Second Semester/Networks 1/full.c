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

ssize_t fullWrite(int fd,const void *buf,size_t count)
{
	size_t left=count;
	ssize_t written;
	while(left>0)
	{
		written=write(fd,buf,left)
		if(written<0)
			if(errno!=EINTR)
				return written;
		left-=written;
		buf+=written;
	}
	return left;
}

ssize_t fullRead(int fd, void *buf, size_t count)
{
	size_t left=count;
	ssize_t nread;
	bool end=false;
	while(left>0 && !end)
	{
		nread=read(fd,buf,left)
		if(nread<0)
			if(errno!=EINTR)
				return nread;
		if(nread==0) end=true;
		left-=nread;
		buf+=nread;
	}
	return left;
}

int xsocket(int typeAddress, int typePort, int protocol)
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

int xbind(int socket, const struct sockaddr *address,socklen_t length)
{
	int ret=bind(socket,address,length);
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

int xconnect(int socket,const struct sockaddr *address,socklen_t length)
{
	int ret=connect(socket,address,length);
	if(ret
}
