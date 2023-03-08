#include "basic.h"

int main(int argc, char **argv) {
	int sockfd, len, n, servPort;
	char buff[MAXLINE], conv[10];

	struct sockaddr_in servaddr, cliaddr;

	servPort = atoi(argv[1]);

	if (argc != 2)
		err_quit("Usage: %s <port>\n", argv[0]);
	while (servPort < 10000 || servPort > 12000) {
		printf("Insert a port between 10000 and 12000 please\n");
		servPort = atoi(fgets(conv, sizeof(conv), stdin));
	}

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");

	memset(&servaddr, '\0', sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(servPort);

	if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");

	while (1) {
		len = sizeof(servaddr);
		memset(buff, '\0', MAXLINE);
		if ((n = recvfrom(sockfd, buff, MAXLINE, 0,
				(struct sockaddr *) &cliaddr, (socklen_t *) &len)) < 0)
			err_sys("recvfrom error");
		printf("Clients info: %s\n", inet_ntoa(cliaddr.sin_addr));
		printf("Data: %s\n", buff);
		buff[n] = '\0';
		strcpy(buff, "Heya to you!");
		if ((n = sendto(sockfd, buff, MAXLINE, 0, (struct sockaddr *) &cliaddr,
				len)) < 0)
			err_sys("sendto error");
	}
	close(sockfd);
}
