#include "basic.h"
#include "my_signal.h"

int main(int argc, char **argv) {
	int sockfd, n, servPort;
	struct sockaddr_in servaddr, replyaddr;
	char buff[MAXLINE], conv[10];
	struct hostent *hostname;
	socklen_t replylen, servLen;

	signal(SIGALRM, gestisci_alarm);

	servPort = atoi(argv[2]);

	if (argc != 3)
		err_quit("Usage: %s <IP address> <port>\n", argv[0]);
	while (servPort < 10000 || servPort > 12000) {
		printf("Insert a port between 10000 and 12000 please\n");
		servPort = atoi(fgets(conv, sizeof(conv), stdin));
	}

	if ((hostname = gethostbyname(argv[1])) == NULL) {
		printf("Host \"%s\" not found!\n", argv[1]);
		return 0;
	}

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");

	memset(&servaddr, '\0', sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = ((struct in_addr *) (hostname->h_addr))->s_addr;
	servaddr.sin_port = htons(servPort);

	servLen = sizeof(servaddr);
	strcpy(buff, "Hello UDP server!");
	if ((n = sendto(sockfd, buff, MAXLINE, 0, (struct sockaddr *) &servaddr,
			servLen)) < 0)
		err_sys("sendto error");
	memset(buff, '\0', MAXLINE);
	memset(&replyaddr, '\0', sizeof(replyaddr));
	alarm(5);
	if ((n = recvfrom(sockfd, buff, MAXLINE, 0, (struct sockaddr *) &replyaddr,
			&replylen)) < 0)
		err_sys("recvfrom error");
	alarm(0);
	signal(SIGALRM, SIG_DFL);
	if ((replylen != servLen) || (memcmp(&servaddr, &replyaddr, replylen) != 0))
		printf("Answer from unknown host\n");
	printf("Data: %s\n", buff);
	close(sockfd);
	exit(0);
}
