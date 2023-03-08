#include "basic.h"
#include "my_functions.h"

int main(int argc, char **argv) {
	int sockfd, connfd, n, servPort, found, line_num;
	char buff[MAXLINE], conv[10], search[100], fileName[50], temp[100];
	socklen_t clilen;
	FILE *fp;

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
		found = 0, line_num = 1;
		clilen = sizeof(struct sockaddr_in);
		if ((connfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen))
				< 0)
			err_sys("accept error\n");

		printf("Client information: %s %d\n", inet_ntoa(cliaddr.sin_addr),
				ntohs(cliaddr.sin_port));

		memset(buff, '\0', sizeof(buff));
		if ((n = read(connfd, buff, MAXLINE)) > 0) {
			if (!(parseLine(buff, fileName, search))) {
				if ((fp = fopen(fileName, "r"))) {
					while (fgets(temp, 100, fp) != NULL) {
						if (strstr(temp, search) != NULL) {
							memset(buff, '\0', sizeof(buff));
							strcpy(buff, "String \"");
							strcat(buff, search);
							strcat(buff, "\" found at line ");
							sprintf(conv, "%d", line_num);
							strcat(buff, conv);
							strcat(buff, "\n");
							found++;
						}
						line_num++;
					}
					if (!found) {
						memset(buff, '\0', sizeof(buff));
						strcpy(buff, "String \"");
						strcat(buff, search);
						strcat(buff, "\" wasn't found in the file\n");
					}
				} else {
					memset(buff, '\0', sizeof(buff));
					strcpy(buff, "File \"");
					strcat(buff, fileName);
					strcat(buff, "\" doesn't exist\n");
				}
			} else {
				memset(buff, '\0', sizeof(buff));
				strcpy(buff, "Message in the wrong format\n");
			}
		}
		if (n < 0)
			printf("read error");
		if ((write(connfd, buff, strlen(buff))) != strlen(buff))
			err_sys("write error");

		close(connfd);
	}
	close(sockfd);
}
