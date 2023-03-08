#include "basic.h"
#include "my_signal.h"

int main(int argc, char **argv) {
	int sockfd, connfd, n, servPort;
	pid_t pid;
	char buff[MAXLINE], conv[10];
	socklen_t clilen;

	struct sockaddr_in servaddr, cliaddr;

	/* setting handler for SIGCHLD */
	signal(SIGCHLD, gestisci_zombie);

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
				< 0) {
			if (errno == EINTR)
				continue;
			else
				err_sys("accept error");
		}

		// child work
		if (!(pid = fork())) {
			// close father socket fd
			close(sockfd);
			printf("Client information: %s %d\n", inet_ntoa(cliaddr.sin_addr),
					ntohs(cliaddr.sin_port));

			time_t ticks = time(NULL);
			snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

			if ((n = write(connfd, buff, strlen(buff))) != strlen(buff))
				err_sys("write error");
			// close child socket fd
			close(connfd);
			exit(0);
		}
		close(connfd);

	}
	close(sockfd);
}
