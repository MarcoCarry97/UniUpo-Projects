#include "basic.h"

int main(int argc, char **argv) {
	int sockfd, n, i, j, servPort;
	struct sockaddr_in servaddr;
	struct timeval starttime, endtime;
	char buff[MAXLINE], intBuff[MAXLINE], conv[10];
	long average = 0;
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
	i = atoi(fgets(intBuff, sizeof(intBuff), stdin));
	snprintf(buff, sizeof(buff), "%d", i);
	if ((write(sockfd, buff, strlen(buff))) != strlen(buff))
		err_sys("write error");
	for (j = 0; j < i; j++) {
		printf("What's the #%d you want to send? ", j + 1);
		memset(buff, '\0', sizeof(buff));
		fgets(buff, MAXLINE, stdin);
		gettimeofday(&starttime, NULL);
		if ((write(sockfd, buff, strlen(buff))) != strlen(buff))
			err_sys("write error");
		memset(buff, '\0', sizeof(buff));
		n = read(sockfd, buff, MAXLINE);
		if (n < 0)
			printf("read error");
		gettimeofday(&endtime, NULL);
		long et_sec = endtime.tv_sec - starttime.tv_sec;
		long et_usec = endtime.tv_usec - starttime.tv_usec;
		printf("String lenght(counting \\n too): %s\nTime: %lu Sec %lu uSec\n",
				buff, et_sec, et_usec);
		average = average + (1000000 * et_sec + et_usec);
	}
	average = (average / i);
	printf("\nAverage = %lu uSec\n", average);

	close(sockfd);
	exit(0);
}
