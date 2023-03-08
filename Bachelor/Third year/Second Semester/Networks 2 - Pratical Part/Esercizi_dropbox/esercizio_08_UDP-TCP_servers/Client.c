#include "basic.h"
#include "my_functions.h"

int main(int argc, char **argv) {
	int sockfdTCP, sockfdUDP, n, servPort;
	struct sockaddr_in servTCPaddr, servUDPaddr;
	char buff[MAXLINE], conv[10];
	struct hostent *hostname;
	infoRcv info;

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

	if ((sockfdTCP = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	servTCPaddr.sin_family = AF_INET;
	servTCPaddr.sin_addr.s_addr =
			((struct in_addr *) (hostname->h_addr))->s_addr;
	servTCPaddr.sin_port = htons(servPort);

	if (connect(sockfdTCP, (struct sockaddr *) &servTCPaddr,
			sizeof(servTCPaddr)) < 0)
		err_sys("connect error");

	clear(buff);
	while ((n = read(sockfdTCP, buff, MAXLINE)) > 0)
		;
	if (n < 0)
		printf("read error");
	if (!(parseLine(buff, &info))) {
		printf("Received info: \n\tHostname: %s\n\tPort: %s\n", info.hostRcv,
				info.portRcv);

		if ((sockfdUDP = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
			err_sys("socket error");

		memset(&servUDPaddr, '\0', sizeof(servUDPaddr));
		servUDPaddr.sin_family = AF_INET;
		servUDPaddr.sin_addr.s_addr = inet_addr(info.hostRcv);
		servUDPaddr.sin_port = htons(atoi(info.portRcv));

		if (connect(sockfdUDP, (struct sockaddr *) &servUDPaddr,
				sizeof(servUDPaddr)) < 0)
			err_sys("connect error");

		clear(buff);
		strcpy(buff, "77.238.178.122");
		if ((write(sockfdUDP, buff, strlen(buff))) != strlen(buff))
			err_sys("write error");
		clear(buff);
		if ((n = read(sockfdUDP, buff, MAXLINE)) > 0)
			printf("Data: %s\n", buff);
		if (n < 0)
			printf("read error");
		close(sockfdUDP);
	} else
		printf("Invalid answer from TCP server\n");

	close(sockfdTCP);
	exit(0);
}
