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

//ssize_t fullWrite(int fd,const void *buf,size_t count);
//ssize_t fullRead(int fd, void *buf, size_t count);
int xsocket(int typeAddress, int typePort,int protocol);
int xbind(int socket, const struct sockaddr_in *address,socklen_t length);
int xconnect(int socket,const struct sockaddr_in *address,socklen_t length);
int xlisten(int socket, int backlog);
int xaccept(int socket, struct sockaddr_in *restrict address, socklen_t *restrict length);
size_t xwrite(int fd,void *buf, size_t bytes);
size_t xread(int fd,void *buf, size_t bytes);
int xclose(int fd);



