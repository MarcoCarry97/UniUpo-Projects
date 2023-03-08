#include "basic.h"
#define WAITTIME 5
#define MAXWAIT 3

int main(int argc, char **argv) {
	int sockfd, n, m, servPort, maxd, rcv = 1, count = 0;
	struct sockaddr_in servaddr;
	char buff[MAXLINE], intBuff[MAXLINE], conv[10];
	struct hostent *hostname;
	struct timeval wait;
	fd_set rset;

	wait.tv_sec = WAITTIME;

	memset(buff, '\0', sizeof(buff));
	memset(intBuff, '\0', sizeof(intBuff));

	servPort = atoi(argv[2]);

	if (argc != 3)
		err_quit("Usage: %s <IP address> <port>\n", argv[0]);
	while (servPort < 10000 || servPort > 12000) {
		printf("Insert a port between 10000 and 12000 please\n");
		servPort = atoi(fgets(conv, sizeof(conv), stdin));
	}

	if ((hostname = gethostbyname(argv[1])) == NULL) {
		printf("Host \"%s\" non trovato!\n", argv[1]);
		return 0;
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = ((struct in_addr *) (hostname->h_addr))->s_addr;
	servaddr.sin_port = htons(servPort);

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	printf("What string do you want to send? ");
	fflush(stdout);
	FD_ZERO(&rset);
	while (rcv) {
		FD_SET(1, &rset);
		FD_SET(sockfd, &rset);
		maxd = MAX(1, sockfd) + 1;
		if ((m = select(maxd, &rset, NULL, NULL, &wait)) < 0)
			err_sys("select error");
		if (m == 0) {
			if (count == MAXWAIT) {
				printf("Closing socket. You took really too long, bye\n");
				close(sockfd);
				exit(0);
			}
			printf("You are waiting too long\n");
			wait.tv_sec = WAITTIME;
			count++;
		}
		if (FD_ISSET(1, &rset)) {
			if (!fgets(buff, MAXLINE, stdin))
				return -1;
			if ((write(sockfd, buff, strlen(buff))) != strlen(buff))
				err_sys("write error");
		}
		if (FD_ISSET(sockfd, &rset)) {
			if ((n = readline(sockfd, intBuff, MAXLINE)) < 0)
				err_sys("readline error");
			if (n == 0)
				err_quit("server died prematurely");
			if (fputs(buff, stdout) == EOF)
				err_sys("fputs error");
			rcv = 0;
		}
	}

	close(sockfd);
	exit(0);
}
