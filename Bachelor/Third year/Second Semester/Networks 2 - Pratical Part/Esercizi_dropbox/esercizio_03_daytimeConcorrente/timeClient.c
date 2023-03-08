#include "basic.h"

int main(int argc, char **argv) {
	int sockfd, n, servPort;
	struct sockaddr_in servaddr;
	char buff[MAXLINE], conv[10];
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

	//ciclo necessario perchè non è certo che riesca a leggere tutti
	//i byte in un unica "read".
	while ((n = read(sockfd, buff, MAXLINE)) > 0) {
		buff[n] = '\0'; //termino con il carattere nullo
		//per poter stampare la stringa
		printf("%s", buff);
	}
	if (n < 0)
		printf("read error");

	close(sockfd);
	exit(0);
}
