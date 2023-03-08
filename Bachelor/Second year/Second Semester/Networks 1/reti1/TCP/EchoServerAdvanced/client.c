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

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		fprintf(stderr,"Usage: %s server port\n",argv[0]);
		exit(0);
	}
	int sock=0, port=atoi(argv[2]);
	char buffer[256]="";
	struct sockaddr_in server;
	sock=xsocket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	memset(&server,'\0',sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_port=htons(port);
	xconnect(sock,&server,sizeof(server));
	//INSERIRE CODICE QUI
	int num=0;
	printf("Inserire numero\n");
	scanf("%d",&num);
	xwrite(sock,&num,sizeof(int));
	for(int i=0;i<num;i++)
	{
		memset(buffer,'/0',sizeof(buffer));
		printf("inserire stringa\n");
		scanf("%s",buffer);
		xwrite(sock,buffer,sizeof(buffer));
		memset(buffer,'/0',sizeof(buffer));
		xread(sock,buffer,sizeof(buffer));
		printf("%s\n",buffer);
		
	}
	//DOPO QUESTO COMMENTO, NON INSERIRE ALTRO CODICE
	xclose(sock);	
	return 0;
}
