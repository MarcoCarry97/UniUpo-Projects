#include "basic.h"

int main(int argc, char **argv) {
	int sockfd, connfd, n, servPort;
	char buff[MAXLINE], conv[10];
	socklen_t clilen;

	struct sockaddr_in servaddr, cliaddr;

	servPort = atoi(argv[1]);

	if (argc != 2)
		err_quit("Usage: %s <port>\n", argv[0]);
	while (servPort < 10000 || servPort > 12000) {
		printf("Insert a port between 10000 and 12000 please\n");
		servPort = atoi(fgets(conv, sizeof(conv), stdin));
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(servPort);

	if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");

	if (listen(sockfd, LISTENQ) < 0)
		err_sys("lister error");

	while (1) {
		clilen = sizeof(struct sockaddr_in);
		if ((connfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen))
				< 0)
			err_sys("accept error\n");

		printf("Client information: %s %d\n", inet_ntoa(cliaddr.sin_addr),
				ntohs(cliaddr.sin_port));

		memset(buff, '\0', sizeof(buff));
		while ((n = read(connfd, buff, MAXLINE)) > 0) {
			printf("Received: %s", buff);
			if ((write(connfd, buff, strlen(buff))) != strlen(buff))
				err_sys("write error");
			memset(buff, '\0', sizeof(buff));
		}
		if (n < 0)
			printf("read error");

		close(connfd);

	}
	close(sockfd);
}
