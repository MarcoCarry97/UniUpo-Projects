#include "basic.h"
#include "my_functions.h"

int main(int argc, char **argv) {
	int sockfd, n, servPort;
	struct sockaddr_in servaddr;
	char buff[MAXLINE], conv[10];
	struct hostent *hostname;
	infoRcv info;
	socklen_t len;

	servPort = atoi(argv[2]);

	if (argc != 3)
		err_quit("Usage: %s <IP address> <port>\n", argv[0]);
	while (servPort < 10000 || servPort > 12000) {
		printf("Insert a port between 10000 and 12000 please\n");
		servPort = atoi(fgets(conv, sizeof(conv), stdin));
	}

	if ((hostname = gethostbyname(argv[1])) == NULL) {
		printf("Host \"%s\" not found!\n", argv[1]);
		return 0;
	}

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");

	clear(&servaddr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = ((struct in_addr *) (hostname->h_addr))->s_addr;
	servaddr.sin_port = htons(servPort);

	len = sizeof(servaddr);
	clear(buff);
	strcpy(buff, "Hello UDP server! Can i have an URL please?");
	if ((n = sendto(sockfd, buff, MAXLINE, 0, (struct sockaddr *) &servaddr,
			len)) < 0)
		err_sys("sendto error");
	//memset(buff, '\0', MAXLINE);
	clear(buff);
	if ((n = recvfrom(sockfd, buff, MAXLINE, 0, (struct sockaddr *) &servaddr,
			&len)) < 0)
		err_sys("recvfrom error");
	if (!(parseLine(buff, &info)))
		printf("Received info: \n\tProtocol: %s\n\tHostname: %s\n\tPort: %s\n",
				info.protRcv, info.hostRcv, info.portRcv);
	else
		printf("%s", buff);
	close(sockfd);
	exit(0);
}
