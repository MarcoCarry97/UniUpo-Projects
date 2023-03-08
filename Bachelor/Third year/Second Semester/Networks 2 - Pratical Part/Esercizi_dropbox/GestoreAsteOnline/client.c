#include "basic.h"
#include "my_functions.h"

int main(int argc, char **argv) {
	int dirsockfd, sockfd = 0, dirServPort, maxd, n, action = 0, try,
			client_id = 0;
	char buff[MAXLINE], intBuff[MAXLINE], conv[10];
	struct hostent *hostname;
	struct sockaddr_in dirservaddr, servaddr;
	fd_set rset, allset;

	if (argc != 3)
		err_quit("Usage: %s <IP address> <port>\n", argv[0]);

	dirServPort = atoi(argv[2]);

	while (dirServPort < 10000 || dirServPort > 12000) {
		printf("Insert a port between 10000 and 12000 please\n");
		dirServPort = atoi(fgets(conv, sizeof(conv), stdin));
	}

	if ((hostname = gethostbyname(argv[1])) == NULL) {
		printf("Host \"%s\" non trovato!\n", argv[1]);
		return 0;
	}

	if ((dirsockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	dirservaddr.sin_family = AF_INET;
	dirservaddr.sin_addr.s_addr =
			((struct in_addr *) (hostname->h_addr))->s_addr;
	dirservaddr.sin_port = htons(dirServPort);

	if (connect(dirsockfd, (struct sockaddr *) &dirservaddr,
			sizeof(dirservaddr)) < 0)
		err_sys("connect error");

	memset(buff, '\0', sizeof(buff));
	if (!strcpy(buff, NEW_CLIENT_STRING))
		return -1;
	if ((write(dirsockfd, buff, strlen(buff))) != strlen(buff))
		err_sys("write error");

	FD_ZERO(&allset);
	FD_SET(1, &allset);
	FD_SET(dirsockfd, &allset);
	maxd = MAX(1, dirsockfd);

	while (1) {
		rset = allset;

		if ((select(maxd + 1, &rset, NULL, NULL, NULL)) < 0)
			err_sys("select error");

		/* The user is inserting some input */
		if (FD_ISSET(1, &rset)) {
			memset(intBuff, '\0', sizeof(intBuff));
			memset(buff, '\0', sizeof(buff));
			if (!fgets(intBuff, MAXLINE, stdin))
				return -1;
			if (strcmp(intBuff, "\n")) {
				switch (action) {
				case 1:
					/* Choosing from the menu to register or login */
					if (!strcpy(buff, CLIENT_LOGIN_REGISTRATION))
						return -1;
					if (!strcat(buff, intBuff))
						return -1;
					break;
				case 2:
					/* Registering as a new user, inserting username */
					if (!strcpy(buff, NEW_CLIENT_REGISTRATION))
						return -1;
					if (!strcat(buff, CLIENT_USERNAME))
						return -1;
					if (!strcat(buff, intBuff))
						return -1;
					break;
				case 3:
					/* Registering as a new user, inserting password */
					if (!strcpy(buff, NEW_CLIENT_REGISTRATION))
						return -1;
					if (!strcat(buff, CLIENT_PASSWORD))
						return -1;
					if (!strcat(buff, intBuff))
						return -1;
					break;
				case 4:
					/* Registering as a new user, confirming password */
					if (!strcpy(buff, NEW_CLIENT_REGISTRATION))
						return -1;
					if (!strcat(buff, CLIENT_PASSWORD_CONFIRM))
						return -1;
					if (!strcat(buff, intBuff))
						return -1;
					break;
				case 11:
					/* Loggin in, inserting username */
					if (!strcpy(buff, CLIENT_LOGIN))
						return -1;
					if (!strcat(buff, CLIENT_USERNAME))
						return -1;
					if (!strcat(buff, intBuff))
						return -1;
					break;
				case 12:
					/* Loggin in, inserting password */
					if (!strcpy(buff, CLIENT_LOGIN))
						return -1;
					if (!strcat(buff, CLIENT_PASSWORD))
						return -1;
					if (!strcat(buff, intBuff))
						return -1;
					break;

				case 101:
					/* Choosing from server menu */
					sprintf(conv, "%d", client_id);
					if (!strcpy(buff, conv))
						return -1;
					if (!strcat(buff, "_"))
						return -1;
					if (!strcat(buff, SELECT_MENU))
						return -1;
					if (!strcat(buff, intBuff))
						return -1;
					break;
				case 102:
					/* Result from a search, select one item or 0 to go back to main menu */
					sprintf(conv, "%d", client_id);
					if (!strcpy(buff, conv))
						return -1;
					if (!strcat(buff, "_"))
						return -1;
					if (!strcat(buff, SEARCH_SELECT))
						return -1;
					if (!strcat(buff, intBuff))
						return -1;
					break;
				case 103:
					/* Result from a search, select one item or 0 to go back to main menu */
					sprintf(conv, "%d", client_id);
					if (!strcpy(buff, conv))
						return -1;
					if (!strcat(buff, "_"))
						return -1;
					if (!strcat(buff, SEARCH_BY_NAME_CLIENT))
						return -1;
					if (!strcat(buff, "'%"))
						return -1;
					if (!strcat(buff, remove_new_line(intBuff)))
						return -1;
					if (!strcat(buff, "%'"))
						return -1;
					break;
				case 104:
					/* Result from a search, select one item or 0 to go back to main menu */
					sprintf(conv, "%d", client_id);
					if (!strcpy(buff, conv))
						return -1;
					if (!strcat(buff, "_"))
						return -1;
					if(!strcat(buff, SELL_ITEM_RESPONSE))
						return -1;
					if (!strcat(buff, remove_new_line(intBuff)))
						return -1;
					break;

				default:
					break;
				}
				if (action > 0 && action < 20) {
					if ((write(dirsockfd, buff, strlen(buff))) != strlen(buff))
						err_sys("write error");
				} else if (action > 100 && action < 120) {
					if (sockfd) {
						if ((write(sockfd, buff, strlen(buff))) != strlen(buff))
							err_sys("write error");
					} else {
						printf("Not connected to any server. Can't send data.");
					}
				}
			}
		}

		if (FD_ISSET(dirsockfd, &rset)) {
			memset(buff, '\0', sizeof(buff));
			if ((n = read(dirsockfd, buff, MAXLINE)) < 0)
				err_sys("read error");
			if (n == 0) {
				/* If the client is connected to a server, continue that session */
				if (sockfd) {
					err_msg(
							"directory server died prematurely. If you are already connected to a server, you will continue your session");
					FD_CLR(dirsockfd, &allset);
				}
				/* Else just quit the program */
				else
					err_quit("directory server died prematurely");
			} else {
				printf("%s", buff);
				if (strcmp(buff, WELCOME_CLIENT) == 0
						|| strcmp(buff, WELCOME_CLIENT_WRONG_LOGIN) == 0
						|| strcmp(buff, NEW_CLIENT_REGISTRATION_ERROR) == 0
						|| strcmp(buff, NEW_CLIENT_REGISTRATION_ERROR_PRESENT)
								== 0
						|| strcmp(buff, NEW_CLIENT_REGISTRATION_COMPLETE) == 0)
					action = 1;
				else if (strcmp(buff, WELCOME_CLIENT_USERNAME) == 0)
					action = 11;
				else if (strcmp(buff, WELCOME_CLIENT_PASSWORD) == 0)
					action = 12;
				else if (strcmp(buff, CLIENT_REGISTRATION_USERNAME) == 0)
					action = 2;
				else if (strcmp(buff, NEW_CLIENT_REGISTRATION_PASSWORD) == 0)
					action = 3;
				else if (strcmp(buff, NEW_CLIENT_REGISTRATION_PASSWORD_REPEAT)
						== 0)
					action = 4;
				else if (strstr(buff, WELCOME_CLIENT_LOGGED)
						|| strstr(buff, RELOGGED)) {
					/* Resetting the counter */
					try = 0;

					char server[50];
					memset(server, '\0', sizeof(server));
					char port[10];
					memset(port, '\0', sizeof(port));
					if (parseSeverAddr(buff, server, port))
						err_msg("wrong input from server");

					if ((client_id = parseId(buff)) < 0)
						err_msg("wrong id");

					if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
						err_sys("socket error");

					servaddr.sin_family = AF_INET;
					servaddr.sin_addr.s_addr = inet_addr(server);
					servaddr.sin_port = htons(atoi(port));

					if (connect(sockfd, (struct sockaddr *) &servaddr,
							sizeof(servaddr)) < 0)
						err_sys("connect error");

					FD_SET(sockfd, &allset);

					if (sockfd > maxd)
						maxd = sockfd;

				} else if (strstr(buff, NO_SERVERS)
						|| strstr(buff, NO_MORE_SERVERS)) {
					if (try++ < TRIES) {
						printf(" - %d of %d\n", try, TRIES);
						sleep(5);
						memset(buff, '\0', sizeof(buff));
						if (!strcpy(buff, RELOGGING))
							return -1;
						if ((write(dirsockfd, buff, strlen(buff)))
								!= strlen(buff))
							err_sys("write error");
					} else {
						printf(
								"\nNo server connected. Please retry at a later time\n");
						close(dirsockfd);
						exit(0);
					}
				}
			}
		}

		if (FD_ISSET(sockfd, &rset)) {
			memset(buff, '\0', sizeof(buff));
			if ((n = read(sockfd, buff, MAXLINE)) < 0)
				err_sys("read error");
			if (n == 0) {
				FD_CLR(sockfd, &allset);
				close(sockfd);
				sockfd = 0;
				printf("server died, looking if there's another server up\n");
				try++;
				sleep(5);
				memset(buff, '\0', sizeof(buff));
				if (!strcpy(buff, RELOGGING))
					return -1;
				if ((write(dirsockfd, buff, strlen(buff))) != strlen(buff))
					err_sys("write error");
			} else {
				printf("%s", buff);
				if (strstr(buff, MENU))
					action = 101;
				/* Receiving results of a search */
				else if (strstr(buff,
						"id\t\tname\t\tstart_date\t\tend_date\t\tseller_id\t\tactual_price")) {
					action = 102;
				}
				/* Searching an item by name */
				else if (strstr(buff, SEARCH_BY_NAME)) {
					action = 103;
				}
				/* Sell an item */
				else if (strstr(buff, SELL_ITEM)) {
					action = 104;
				}
				/* The user finished his session */
				else if (strstr(buff, GOODBYE)) {
					/* Quitting */
					if (!strcpy(buff, CLIENT_GOODBYE))
						return -1;
					if (!strcat(buff, GOODBYE_OK))
						return -1;

					/* Closing connection both to the server and to the directory server */
					if ((write(sockfd, buff, strlen(buff))) != strlen(buff))
						err_sys("write error");
					if ((write(dirsockfd, buff, strlen(buff))) != strlen(buff))
						err_sys("write error");

					close(sockfd);
					close(dirsockfd);
					exit(0);
				}

			}
		}
	}

	close(dirsockfd);
	exit(0);
}
