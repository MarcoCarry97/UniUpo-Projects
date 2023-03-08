#include "basic.h"

int main(int argc, char **argv) {
	int sockfd, n, i, j, servPort;
	struct sockaddr_in servaddr;
	char buff[MAXLINE], intBuff[MAXLINE], conv[10];
	struct hostent *hostname;

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

	printf("How many strings do you want to send? ");
	i = atoi(fgets(intBuff, sizeof(buff), stdin));
	snprintf(conv, sizeof(conv), "%d", i);
	if ((write(sockfd, conv, strlen(conv))) != strlen(conv))
		err_sys("write error");
	for (j = 0; j < (i + 1); j++) {
		printf("What's the #%d you want to send? ", j + 1);
		fgets(buff, MAXLINE, stdin);
		if ((write(sockfd, buff, strlen(buff))) != strlen(buff))
			err_sys("write error");
		memset(intBuff, '\0', sizeof(intBuff));
		//n = read(sockfd, intBuff, MAXLINE);
		n = readline(sockfd, intBuff, MAXLINE);
		if (n < 0)
			printf("read error");
		printf("%s", intBuff);
	}

	close(sockfd);
	exit(0);
}
