#include "basic.h"
#include "my_functions.h"

int main(int argc, char **argv) {
	int sockfd, n, servPort, maxd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE], intBuff[MAXLINE], conv[10];
	struct hostent *hostname;
	fd_set rset;

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

	FD_ZERO(&rset);
	while (!(strstr(intBuff, "END"))) {
		FD_SET(1, &rset);
		FD_SET(sockfd, &rset);
		maxd = MAX(1, sockfd) + 1;
		if ((select(maxd, &rset, NULL, NULL, NULL)) < 0)
			err_sys("select error");
		/* The user is inserting some input */
		if (FD_ISSET(1, &rset)) {
			memset(buff, '\0', sizeof(buff));
			if (!fgets(buff, MAXLINE, stdin))
				return -1;
			if ((write(sockfd, buff, strlen(buff))) != strlen(buff))
				err_sys("write error");
		}
		/* Receiving some data from the server */
		if (FD_ISSET(sockfd, &rset)) {
			memset(intBuff, '\0', sizeof(intBuff));
			if ((n = read(sockfd, intBuff, MAXLINE)) < 0)
				err_sys("read error");
			if (n == 0)
				err_quit("server died prematurely");
			buff[n] = '\0';
			printf("%s", intBuff);
		}
	}

	close(sockfd);
	exit(0);
}
