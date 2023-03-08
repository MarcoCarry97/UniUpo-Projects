#include "basic.h"

int main(int argc, char **argv) {
	int sockfd, connfd, listenfd, n, servPort, i, j, k, maxi, maxd, ready,
			numClients = 0;
	char buff[MAXLINE], intBuff[MAXLINE], conv[10];
	fd_set rset, allset;
	socklen_t clilen;

	struct sockaddr_in servaddr, cliaddr;
	typedef struct clients {
		int fd;
		char name[25];
	} clients;

	clients client[FD_SETSIZE];

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

	maxd = sockfd;
	client[0].fd = sockfd;
	strcpy(client[0].name, "Welcome socket");
	maxi = -1;
	for (i = 1; i < FD_SETSIZE; i++) {
		client[i].fd = -1;
		memset(client[i].name, '\0', sizeof(client[i].name));
	}
	FD_ZERO(&allset);
	FD_SET(sockfd, &allset);
	system("clear");

	while (1) {
		rset = allset;
		if ((ready = select(maxd + 1, &rset, NULL, NULL, NULL)) < 0)
			err_sys("select error\n");

		/* New client connecting */
		if (FD_ISSET(client[0].fd, &rset)) {
			clilen = sizeof(cliaddr);
			if ((connfd = accept(client[0].fd, (struct sockaddr *) &cliaddr,
					&clilen)) < 0)
				err_sys("accept error\n");

			for (i = 1; i < FD_SETSIZE; i++)
				if (client[i].fd < 0) {
					client[i].fd = connfd;
					printf("Client information: %s %d\n",
							inet_ntoa(cliaddr.sin_addr),
							ntohs(cliaddr.sin_port));
					break;
				}

			if (i == FD_SETSIZE)
				err_quit("too many clients\n");
			FD_SET(connfd, &allset);
			numClients++;
			if (connfd > maxd)
				maxd = connfd;
			if (i > maxi)
				maxi = i;
			if (--ready <= 0)
				continue;
		}

		/* Checking if received something from the clients */
		for (i = 1; i <= maxi; i++) {
			if ((listenfd = client[i].fd) < 0)
				continue;
			if (FD_ISSET(listenfd, &rset)) {
				memset(buff, '\0', sizeof(buff));
				if ((n = read(listenfd, buff, MAXLINE)) == 0) {
					if (close(listenfd) == -1)
						err_sys("close error\n");
					FD_CLR(listenfd, &allset);
					client[i].fd = -1;
					numClients--;
				} else {
					if (strlen(client[i].name) == 0) {
						strcpy(client[i].name, buff);
						printf("Client %s %d, has now name %s",
								inet_ntoa(cliaddr.sin_addr),
								ntohs(cliaddr.sin_port), buff);

						/* Build the line to send all actual names */
						memset(intBuff, '\0', sizeof(intBuff));
						strcat(intBuff, "Client connected: ");
						for (k = 1; k <= maxi; k++) {
							strcat(intBuff, strtok(client[k].name, "\n"));
							strcat(intBuff, " ");
						}
						strcat(intBuff, "\n");
						for (j = 1; j <= maxi; j++)
							if (client[j].fd != -1)
								if (write(client[j].fd, intBuff,
										strlen(intBuff)) < 0)
									err_sys("write error\n");
					} else {
						memset(intBuff, '\0', sizeof(intBuff));
						strcat(intBuff, strtok(client[i].name, "\n"));
						strcat(intBuff, " says: ");
						strcat(intBuff, buff);
						printf("Received: %s", intBuff);
						for (j = 1; j <= maxi; j++) {
							if (client[j].fd != -1 && client[j].fd != listenfd)
								if (write(client[j].fd, intBuff,
										strlen(intBuff)) < 0)
									err_sys("write error\n");
						}
					}
				}
				if (--ready <= 0)
					break;
			}
		}
	}
	close(client[0].fd);
}
