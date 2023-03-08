#include "basic.h"
#include "list.h"
#include "my_signal.h"
#include "my_functions.h"
#include "mysql.h"

int main(int argc, char **argv) {
	int dirsockfd, sockfd, connfd, dirServPort, servPort, n, first = 1;
	char buff[BUFFSIZE], intBuff[BUFFSIZE], conv[10];
	pid_t pid;
	struct hostent *hostname;
	struct sockaddr_in dirServaddr, servaddr, cliaddr;
	socklen_t clilen;

	if (argc != 4)
		err_quit("Usage: %s <IP address> <port_of_directory_server> <port>\n",
				argv[0]);

	/* Port of the directory server it has to connect to */
	dirServPort = atoi(argv[2]);
	/* Port of this server, that will receive the clients */
	servPort = atoi(argv[3]);

	while (dirServPort < 10000 || dirServPort > 12000) {
		printf("Insert a port between 10000 and 12000 please\n");
		dirServPort = atoi(fgets(conv, sizeof(conv), stdin));
	}

	while (servPort < 10000 || servPort > 12000 || servPort == dirServPort) {
		printf(
				"Insert a port between 10000 and 12000 please, different from the one of the directory server\n");
		servPort = atoi(fgets(conv, sizeof(conv), stdin));
	}

	/* Acting like a server */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(servPort);

	if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");

	if (listen(sockfd, LISTENQ) < 0)
		err_sys("lister error");

	/* setting handler for SIGCHLD */
	signal(SIGCHLD, gestisci_zombie);

	/* Acting like a client */
	if ((hostname = gethostbyname(argv[1])) == NULL) {
		printf("Host \"%s\" non trovato!\n", argv[1]);
		return 0;
	}

	if ((dirsockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	dirServaddr.sin_family = AF_INET;
	dirServaddr.sin_addr.s_addr =
			((struct in_addr *) (hostname->h_addr))->s_addr;
	dirServaddr.sin_port = htons(dirServPort);

	if (connect(dirsockfd, (struct sockaddr *) &dirServaddr,
			sizeof(dirServaddr)) < 0)
		err_sys("connect error");

	memset(buff, '\0', sizeof(buff));
	if (!strcpy(buff, NEW_SERVER_STRING))
		return -1;
	if (!strcat(buff, argv[3]))
		return -1;
	if ((write(dirsockfd, buff, strlen(buff))) != strlen(buff))
		err_sys("write error");

	while (1) {
		if (first) {
			memset(buff, '\0', sizeof(buff));
			if ((n = read(dirsockfd, buff, BUFFSIZE)) < 0)
				err_sys("read error");
			if (n == 0)
				err_quit("server died prematurely");
			else
				printf("%s", buff);

			if (create_items_database())
				err_sys("couldn't create the database");

			if (create_bids_database())
				err_sys("couldn't create the database");

			first = 0;
		} else {
			clilen = sizeof(struct sockaddr_in);
			if ((connfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen))
					< 0) {
				if (errno == EINTR)
					continue;
				else
					err_sys("accept error");
			}

			// child work
			if (!(pid = fork())) {
				int first_time = 1;

				// close father socket fd
				close(sockfd);
				printf("Client information: %s %d\n",
						inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

				while (1) {
					if (first_time) {
						first_time = 0;
						memset(buff, '\0', sizeof(buff));
						if (!strcpy(buff, MENU))
							return -1;
						if ((n = write(connfd, buff, BUFFSIZE)) < 0)
							err_sys("write error");
					} else {
						/* Reading what the client is sending */
						memset(buff, '\0', sizeof(buff));
						if ((n = read(connfd, buff, BUFFSIZE)) < 0)
							err_sys("read error");

						printf("Client %s %d: %s", inet_ntoa(cliaddr.sin_addr),
								ntohs(cliaddr.sin_port), buff);

						memset(intBuff, '\0', sizeof(intBuff));
						/* Parsing the line to know what do do */
						if (!strcpy(intBuff, parse(buff)))
							return -1;
						int action = atoi(intBuff);

						/* What menu voice does the client want to select */
						if (strstr(buff, SELECT_MENU)) {
							/* Get id of the client */
							int client_id = 0, num_rows;
							if ((client_id = parseId(buff)) < 0)
								err_msg("wrong id");

							memset(buff, '\0', sizeof(buff));
							switch (action) {
							case 0:
								if (!strcpy(buff, GOODBYE))
									return -1;
								break;
							case 1:
								if (!strcpy(buff, ""))
									return -1;
								num_rows = 0;
								num_rows = get_from_db(SHOW_LATEST_ITEMS, buff);
								if (num_rows >= 1) {
									if (!strcat(buff, SEARCH_MENU))
										return -1;
								} else {
									if (!strcat(buff, NO_RESULTS))
										return -1;
									if (!strcat(buff, MENU))
										return -1;
								}
								break;
							case 2:
								/* Searching by name */
								if (!strcpy(buff, SEARCH_BY_NAME))
									return -1;
								break;
							case 3:
								/* Latest bids */
								memset(buff, '\0', sizeof(buff));
								memset(intBuff, '\0', sizeof(intBuff));

								/* SELECT DISTINCT id, name, start_date, end_date, seller_id, actual_price, actual_winning_user FROM items, (SELECT * FROM bids WHERE user_id = ...) as a WHERE id = a.item_id AND seller_id != a.user_id */
								if (!strcpy(intBuff,
										"SELECT DISTINCT id, name, start_date, end_date, seller_id, actual_price, actual_winning_user FROM items, (SELECT * FROM bids WHERE user_id = "))
									return -1;
								memset(conv, '\0', sizeof(conv));
								sprintf(conv, "%d", client_id);
								if (!strcat(intBuff, conv))
									return -1;
								if (!strcat(intBuff,
										") as a WHERE id = a.item_id AND seller_id != a.user_id"))
									return -1;

								num_rows = 0;
								num_rows = get_from_db(intBuff, buff);
								if (num_rows >= 1) {
									if (!strcat(buff, SEARCH_MENU))
										return -1;
								} else {
									if (!strcat(buff, NO_RESULTS))
										return -1;
									if (!strcat(buff, MENU))
										return -1;
								}
								break;
							case 4:
								/* Items won */
								memset(buff, '\0', sizeof(buff));
								memset(intBuff, '\0', sizeof(intBuff));

								if (!strcpy(intBuff,
										"SELECT * FROM items WHERE end_date < NOW() AND actual_winning_user = "))
									return -1;
								memset(conv, '\0', sizeof(conv));
								sprintf(conv, "%d", client_id);
								if (!strcat(intBuff, conv))
									return -1;

								num_rows = 0;
								num_rows = get_from_db(intBuff, buff);
								if (num_rows < 1) {
									if (!strcat(buff, NO_RESULTS))
										return -1;
								}
								if (!strcat(buff, MENU))
									return -1;
								break;
							case 5:
								/* Items on sale */
								memset(buff, '\0', sizeof(buff));
								memset(intBuff, '\0', sizeof(intBuff));

								if (!strcpy(intBuff,
										"SELECT * FROM items WHERE end_date > NOW() AND seller_id = "))
									return -1;
								memset(conv, '\0', sizeof(conv));
								sprintf(conv, "%d", client_id);
								if (!strcat(intBuff, conv))
									return -1;

								num_rows = 0;
								num_rows = get_from_db(intBuff, buff);
								if (num_rows < 1) {
									if (!strcat(buff, NO_RESULTS))
										return -1;
								}
								if (!strcat(buff, MENU))
									return -1;
								break;
							case 6:
								/* Items on sale */
								memset(buff, '\0', sizeof(buff));
								memset(intBuff, '\0', sizeof(intBuff));

								if (!strcpy(intBuff,
										"SELECT * FROM items WHERE end_date < NOW() AND seller_id = "))
									return -1;
								memset(conv, '\0', sizeof(conv));
								sprintf(conv, "%d", client_id);
								if (!strcat(intBuff, conv))
									return -1;

								num_rows = 0;
								num_rows = get_from_db(intBuff, buff);
								if (num_rows < 1) {
									if (!strcat(buff, NO_RESULTS))
										return -1;
								}
								if (!strcat(buff, MENU))
									return -1;
								break;
							case 7:
								/* Selling an item */
								if (!strcpy(buff, SELL_ITEM))
									return -1;
								break;
							default:
								if (!strcpy(buff, UNKNOWN_MENU))
									return -1;
								break;
							}
							if ((n = write(connfd, buff, BUFFSIZE)) < 0)
								err_sys("write error");
						}
						/* Selecting an item from a search or going back to main menu */
						else if (strstr(buff, SEARCH_SELECT)) {
							/* Get id of the client */
							int client_id = 0;
							if ((client_id = parseId(buff)) < 0)
								err_msg("wrong id");

							if (action == 0) {
								if (!strcpy(buff, MENU))
									return -1;
							} else {
								memset(intBuff, '\0', sizeof(intBuff));
								if (!strcpy(intBuff,
										"SELECT * FROM items WHERE end_date > NOW() AND id = "))
									return -1;
								memset(conv, '\0', sizeof(conv));
								sprintf(conv, "%d", action);
								if (!strcat(intBuff, conv))
									return -1;

								memset(buff, '\0', sizeof(buff));
								int num_rows = get_from_db(intBuff, buff);
								if (num_rows >= 1) {
									if (!strcat(buff, BID))
										return -1;
									memset(conv, '\0', sizeof(conv));
									sprintf(conv, "%d", action);
									if (!strcat(buff, "$"))
										return -1;
									if (!strcat(buff, conv))
										return -1;
									if (!strcat(buff, "\n"))
										return -1;
								} else {
									if (!strcat(buff, NO_RESULTS))
										return -1;
									if (!strcat(buff, MENU))
										return -1;
								}
							}
							if ((n = write(connfd, buff, BUFFSIZE)) < 0)
								err_sys("write error");
						}
						/* The client wants to do a search by name */
						else if (strstr(buff, SEARCH_BY_NAME_CLIENT)) {
							/* Get id of the client */
							int client_id = 0;
							if ((client_id = parseId(buff)) < 0)
								err_msg("wrong id");

							memset(intBuff, '\0', sizeof(intBuff));
							if (!strcpy(intBuff,
									"SELECT * FROM items WHERE name LIKE "))
								return -1;
							//printf("\t\t%s", parse(buff));
							if (!strcat(intBuff, parse(buff)))
								return -1;
							if (!strcat(intBuff, " LIMIT 10"))
								return -1;

							memset(buff, '\0', sizeof(buff));
							int num_rows = get_from_db(intBuff, buff);
							if (num_rows >= 1) {
								if (!strcat(buff, SEARCH_MENU))
									return -1;
							} else {
								if (!strcat(buff, NO_RESULTS))
									return -1;
								if (!strcat(buff, MENU))
									return -1;
							}
							if ((n = write(connfd, buff, BUFFSIZE)) < 0)
								err_sys("write error");
						}
						/* Selling an item */
						else if (strstr(buff, SELL_ITEM_RESPONSE)) {
							/* Get id of the client */
							int client_id = 0;
							if ((client_id = parseId(buff)) < 0)
								err_msg("wrong id");

							memset(intBuff, '\0', sizeof(intBuff));
							if (!strcpy(intBuff,
									"INSERT INTO items (name, start_date, end_date, seller_id, actual_price, actual_winning_user) VALUES (\""))
								return -1;
							if (!strcat(intBuff, parse(buff)))
								return -1;
							if (!strcat(intBuff,
									"\", NOW(), NOW() + INTERVAL 3 DAY, "))
								return -1;
							memset(conv, '\0', sizeof(conv));
							sprintf(conv, "%d", client_id);
							if (!strcat(intBuff, conv))
								return -1;
							if (!strcat(intBuff, ", 1, 0)"))
								return -1;
							if (insert_into_db(intBuff))
								return -1;
							printf(
									"\t\tUser %d is now selling the item requested\n",
									client_id);

							memset(buff, '\0', sizeof(buff));
							if (!strcpy(buff, ITEM_ON_SALE))
								return -1;
							if (!strcat(buff, MENU))
								return -1;

							if ((n = write(connfd, buff, BUFFSIZE)) < 0)
								err_sys("write error");
						}
						/* The client is making a bid */
						else if (strstr(buff, BID_ITEM)) {
							/* Get id of the client */
							int client_id = 0, item_id = 0, price = 0;
							if ((client_id = parseId(buff)) < 0)
								err_msg("wrong id");

							if ((item_id = parseItemId(buff)) < 0)
								err_msg("wrong item id");

							if ((price = parsePrice(buff)) < 0)
								err_msg("wrong item id");

							printf(
									"utente %d, oggetto %d, Prezzo puntato %d \n",
									client_id, item_id, price);
							memset(buff, '\0', sizeof(buff));
							//The user is making a bid
							if (price > 0) {
								if (check_item_bid(client_id, item_id, price,
										buff))
									return -1;
							}

							//The user wants to go back to main menu
							else if (price == 0) {
								if (!strcpy(buff, MENU))
									return -1;
							}
							//Received wrong input
							else {
								if (!strcpy(buff, "Nothing to do\n"))
									return -1;
								if (!strcat(buff, MENU))
									return -1;
							}

							// Answering the client
							if ((n = write(connfd, buff, BUFFSIZE)) < 0)
								err_sys("write error");

						}
						/* The client is quitting */
						else if (strstr(buff, CLIENT_GOODBYE)) {
							close(connfd);
							exit(0);
						}

					}
				}
				// close child socket fd
				close(connfd);
				exit(0);
			}
			// close parent socket fd
			close(connfd);
		}
	}

	close(dirsockfd);
	exit(0);
}
