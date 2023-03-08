#include "basic.h"
#include "my_functions.h"

int main(int argc, char **argv) {
	int sockfd, n, m, servPort, times;
	char buff[MAXLINE], conv[20];
	long timeleft;
	socklen_t len;

	struct sockaddr_in servaddr, cliaddr;
	listClients *list = NULL;

	servPort = atoi(argv[1]);

	if (argc != 2)
		err_quit("Usage: %s <port>\n", argv[0]);
	while (servPort < 10000 || servPort > 12000) {
		printf("Insert a port between 10000 and 12000 please\n");
		servPort = atoi(fgets(conv, sizeof(conv), stdin));
	}

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");

	clear(&servaddr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(servPort);

	if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");

	while (1) {
		len = sizeof(servaddr);
		clear(buff);
		clear(&cliaddr);
		if ((n = recvfrom(sockfd, buff, MAXLINE, 0,
				(struct sockaddr *) &cliaddr, &len)) < 0)
			err_sys("recvfrom error");
		if (!(m = checkClient(cliaddr, len, &list, &times, &timeleft))) {
			printf("Client info: %s\n", inet_ntoa(cliaddr.sin_addr));

			printf("Data: %s\n", buff);
			buff[n] = '\0';
			strcpy(buff, "http://www.cimiteromonumentalealessandria.it:80\n");

		} else {
			if (times == MAXBOTHERING) {
				printf("Client %s is banned for %lu seconds\n",
						inet_ntoa(cliaddr.sin_addr), timeleft);
				clear(buff);
				strcpy(buff, "Not going to answer you anymore for the next ");
				sprintf(conv, "%lu", timeleft);
				strcat(buff, conv);
				strcat(buff, " seconds, bye\n");
			} else if (times > MAXBOTHERING) {
				clear(buff);
			} else {
				clear(buff);
				strcpy(buff, "stop bitching!\n");
			}
		}
		if ((n = sendto(sockfd, buff, MAXLINE, 0, (struct sockaddr *) &cliaddr,
				len)) < 0)
			err_sys("sendto error");
	}
	close(sockfd);
}
