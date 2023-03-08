#include <stdio.h>      
#include <sys/types.h>
#include <sys/socket.h>   
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include<stdlib.h>

const char MESSAGE[] = "Hello UPO student!\n";

int main(int argc, char *argv[]) {

    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    struct sockaddr_in simpleServer;

    if (2 != argc) {

        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);

    }

    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {

        fprintf(stderr, "Could not create a socket!\n");
        exit(1);

    }
    else {
	    fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for listening */
    simplePort = atoi(argv[1]);

    /* setup the address structure */
    /* use INADDR_ANY to bind to all local addresses  */
    memset(&simpleServer, '\0', sizeof(simpleServer)); 
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
    simpleServer.sin_port = htons(simplePort);

    /*  bind to the address and port with our socket  */
    returnStatus = bind(simpleSocket,(struct sockaddr *)&simpleServer,sizeof(simpleServer));

    if (returnStatus == 0) {
	    fprintf(stderr, "Bind completed!\n");
    }
    else {
        fprintf(stderr, "Could not bind to address!\n");
	close(simpleSocket);
	exit(1);
    }

    /* lets listen on the socket for connections      */
    returnStatus = listen(simpleSocket, 5);

    if (returnStatus == -1) {
        fprintf(stderr, "Cannot listen on socket!\n");
	close(simpleSocket);
        exit(1);
    }

    while (1)

    {

        struct sockaddr_in clientName = { 0 };
	int simpleChildSocket = 0;
	int clientNameLength = sizeof(clientName);

	/* wait here */
	char string[100];
	int num=0;
        simpleChildSocket = accept(simpleSocket,(struct sockaddr *)&clientName, &clientNameLength);

	if (simpleChildSocket == -1) {

            fprintf(stderr, "Cannot accept connections!\n");
	    close(simpleSocket);
	    exit(1);

	}

        /* handle the new connection request  */
	/* write out our message to the client */
	//write(simpleChildSocket, MESSAGE, strlen(MESSAGE));
	returnStatus=read(simpleChildSocket,&num,1);
	if(returnStatus >0) printf("ricevuto: %d\n",num);
	for(int i=0;i<num;i++)
	{
		memset(string,'\0',100);
		int num1=0,num2=0;
		char oper;
		returnStatus=read(simpleChildSocket,string,100);
		printf("ricevuta %s\n", string);
		sscanf("%d %d %c",&num1,&num2,&oper);
		int result=0;
		switch(oper)
		{
			case('+'): result=num1+num2; break;
			case('-'): result=num1-num2; break;
			case('*'): result=num1*num2; break;
			case('/'): result=num1/num2; break;
			default: result=0;
		}
		char ret[10];
		memset(ret,'\0',10);
		if(result==0) strcpy(ret,"NACK");
		returnStatus=write(simpleChildSocket,ret,1);
		if(returnStatus>0) printf("inviato %s\n",ret);
	}
        close(simpleChildSocket);

    }

    close(simpleSocket);
    return 0;

}

