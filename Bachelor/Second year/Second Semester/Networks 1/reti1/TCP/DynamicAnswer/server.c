#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>   
#include <netdb.h>
#include <unistd.h>
#include<time.h>
#include"full.h"

char MESSAGE[]="Hello UPO student!";

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		fprintf(stderr,"Usage: %s port\n",argv[0]);
		exit(0);
	}
	int sock=0, port=atoi(argv[1]);
	struct sockaddr_in server;
	sock=xsocket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	memset(&server,'\0',sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons(port);
	xbind(sock,&server,sizeof(server));
	xlisten(sock,5);
	char buffer[256]="";
	bool end=false;
	while(!end)
	{
		struct sockaddr_in client={0};
		int childSock=0;
		int clientLength=sizeof(client);
		childSock=xaccept(sock,&client,&clientLength);
		//INSERIRE CODICE QUI
		memset(buffer,'\0',sizeof(buffer));
		time_t ticks=time(NULL);
		snprintf(buffer,sizeof(buffer),"%.24s\r\n",ctime(&ticks));
		xwrite(childSock,buffer,strlen(buffer));
		//DOPO QUESTO COMMENTO, NON INSERIRE PIù CODICE
		xclose(childSock);
	}
	xclose(sock);
	return 0;	
}
