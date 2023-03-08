#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>   
#include <netdb.h>
#include <unistd.h>
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
    int num=0;
    int length=0;
	bool end=false;
	while(!end)
	{
		struct sockaddr_in client={0};
		int childSock=0;
		int clientLength=sizeof(client);
		childSock=xaccept(sock,&client,&clientLength);
		//INSERIRE CODICE QUI
        xread(childSock,&num,sizeof(int));
        for(int i=0;i<num;i++)
        {
            memset(buffer,'\0',sizeof(buffer));
            xread(childSock,buffer,sizeof(buffer));
            length=strlen(buffer);
            xwrite(childSock,&length,sizeof(int));
        }
		//DOPO QUESTO COMMENTO, NON INSERIRE PIù CODICE
		xclose(childSock);
	}
	xclose(sock);
	return 0;	
}
