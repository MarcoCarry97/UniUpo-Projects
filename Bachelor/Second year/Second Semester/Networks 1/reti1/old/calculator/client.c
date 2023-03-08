#include <stdio.h>      
#include <sys/types.h>
#include <sys/socket.h>   
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

double getTime(struct timeval t);

int main(int argc, char *argv[]) {

    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    char buffer[256] = "";
    struct sockaddr_in simpleServer;

    if (3 != argc) {

        fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
        exit(1);

    }

    /* create a streaming socket      */
    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {

        fprintf(stderr, "Could not create a socket!\n");
        exit(1);

    }
    else {
	    fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for connecting */
    simplePort = atoi(argv[2]);

    /* setup the address structure */
    /* use the IP address sent as an argument for the server address  */
    //bzero(&simpleServer, sizeof(simpleServer)); 
    memset(&simpleServer, '\0', sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    //inet_addr(argv[2], &simpleServer.sin_addr.s_addr);
    simpleServer.sin_addr.s_addr=inet_addr(argv[1]);
    simpleServer.sin_port = htons(simplePort);

    /*  connect to the address and port with our socket  */
    returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

    if (returnStatus == 0) {
	    fprintf(stderr, "Connect successful!\n");
    }
    else {
        fprintf(stderr, "Could not connect to address!\n");
	close(simpleSocket);
	exit(1);
    }

    /* get the message from the server   */
    /*returnStatus = read(simpleSocket, buffer, sizeof(buffer));

    if ( returnStatus > 0 ) {
        printf("%d: %s", returnStatus, buffer);
    } else {
        fprintf(stderr, "Return Status = %d \n", returnStatus);
    }*/
	int num=0;
	char ret[10];
	char string[100];
	printf("inserire numero\n");
	scanf("%d",&num);
	struct timeval startTime,endTime;
	gettimeofday(&startTime,NULL);
	write(simpleSocket,&num,1);
	for(int i=0;i<num;i++)
	{
		int num1=0,num2=0;
		char oper;
		memset(string,'\0',100);
		memset(ret,'\0',10);
		printf("inserire 2 numeri  e un carattere (+,-,*,7) separati da spazio\n");
		scanf("%d %d %c",&num1,&num2,&oper);
		sprintf(string,"%d %d %c",num1,num2,oper);
		write(simpleSocket,string,strlen(string));
		returnStatus=read(simpleSocket,&ret,1);
		if(returnStatus>0)
		{
			if(strcmp(ret,"NACK")==0)
				printf("Uno dei parametri é errato\n");
			else printf("%s\n");
		}
	}
	gettimeofday(&endTime,NULL);
	double serviceTime=getTime(endTime)-getTime(startTime);
	printf("service time: %f\n",serviceTime);
    close(simpleSocket);
    return 0;

}

double getTime(struct timeval t)
{
	return t.tv_sec+(t.tv_usec/1000000.0);
}

