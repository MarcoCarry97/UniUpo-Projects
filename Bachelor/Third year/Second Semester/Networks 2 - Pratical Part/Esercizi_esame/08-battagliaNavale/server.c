#include "basic.h"
#include "my_functions.h"

int main(int argc, char **argv) {
	/* Sockets variables */
	int sockfd, connfd, listenfd;
	/* System variables */
	int servPort, maxi, maxd, ready;
	/* Temporary variables */
	int i, j, k, l, m, n, temp1, temp2;
	/* Buffers */
	char buff[MAXLINE], intBuff[MAXLINE], conv[10], ship;

	fd_set rset, allset;
	socklen_t clilen;

	struct sockaddr_in servaddr, cliaddr;

	clients client[FD_SETSIZE];
	matches match[FD_SETSIZE / 2];

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

	/* Setting the welcome socket */
	maxd = sockfd;
	client[0].fd = sockfd;

	maxi = -1;
	/* Initialize the array */
	for (i = 1; i < FD_SETSIZE; i++) {
		client[i].fd = -1;
		client[i].playingWith = -1;
	}
	for (i = 1; i < (FD_SETSIZE / 2); i++) {
		match[i].turn = -1;
		for (j = 0; j < 2; j++) {
			match[i].info[j].client = -1;
			match[i].info[j].hits = 0;
			match[i].info[j].numShips = 0;
			match[i].info[j].battleships = 0;
			match[i].info[j].corvettes = 0;
			match[i].info[j].submarines = 0;
			match[i].info[j].lances = 0;
		}
	}

	FD_ZERO(&allset);
	FD_SET(sockfd, &allset);

	while (1) {
		rset = allset;
		if ((ready = select(maxd + 1, &rset, NULL, NULL, NULL)) < 0)
			err_sys("select error\n");

		/* New client connecting */
		if (FD_ISSET(client[0].fd, &rset)) {
			clilen = sizeof(cliaddr);
			if ((connfd = accept(client[0].fd, (struct sockaddr *) &cliaddr,
					&clilen)) < 0)
				err_sys("accept error\n");

			for (i = 1; i < FD_SETSIZE; i++)
				if (client[i].fd < 0) {
					client[i].fd = connfd;
					printf("Client information: %s %d\n",
							inet_ntoa(cliaddr.sin_addr),
							ntohs(cliaddr.sin_port));
					break;
				}
			if (i == FD_SETSIZE)
				err_quit("too many clients\n");
			FD_SET(connfd, &allset);
			for (j = 0; j < (FD_SETSIZE / 2); j++) {
				/* Odd number of players */
				if (match[j].info[0].client == -1) {
					match[j].info[0].client = i;
					break;
				}
				/* Creating a new match, setting the first turn randomly */
				else if (match[j].info[1].client == -1) {
					match[j].info[1].client = i;

					/* Index of the opponent client */
					client[match[j].info[0].client].playingWith =
							match[j].info[1].client;
					client[match[j].info[1].client].playingWith =
							match[j].info[0].client;

					/* Deciding turn randomly */
					srand(time(NULL));
					match[j].turn = rand() % 2;

					/* Matrixes initialized to 0 */
					match[j].info[0].moves = (int **) malloc(
					SIDE * sizeof(int *));
					match[j].info[0].ships = (int **) malloc(
					SIDE * sizeof(int *));
					match[j].info[1].moves = (int **) malloc(
					SIDE * sizeof(int *));
					match[j].info[1].ships = (int **) malloc(
					SIDE * sizeof(int *));
					for (k = 0; k < SIDE; k++) {
						match[j].info[0].moves[k] = (int *) calloc(SIDE,
								sizeof(int));
						match[j].info[0].ships[k] = (int *) calloc(SIDE,
								sizeof(int));
						match[j].info[1].moves[k] = (int *) calloc(SIDE,
								sizeof(int));
						match[j].info[1].ships[k] = (int *) calloc(SIDE,
								sizeof(int));
					}
					for (k = 0; k < SIDE; k++)
						for (l = 0; l < SIDE; l++) {
							match[j].info[0].moves[k][l] = 0;
							match[j].info[0].ships[k][l] = 0;
							match[j].info[1].moves[k][l] = 0;
							match[j].info[1].ships[k][l] = 0;
						}

					/*
					 * NEED TO MAKE A FUNCTION TO CREATE THIS BUFFER
					 */

					for (k = 0; k < 2; k++) {
						buffShipPlacement(buff, match[j].info, k);
						if (write(client[match[j].info[k].client].fd, buff,
								strlen(buff)) < 0)
							err_sys("write error\n");
					}

					/* The players need to choose where to put their ship */
					printf("Match %d started between clients %d and %d\n", j,
							match[j].info[0].client, match[j].info[1].client);

					/* Found a free match, don't need to keep searching */
					break;
				}
			}

			/* Should never happen since we would have exited with too many clients error */
			if (j == (FD_SETSIZE / 2))
				err_quit("too many matches\n");
			if (connfd > maxd)
				maxd = connfd;
			if (i > maxi)
				maxi = i;
			if (--ready <= 0)
				continue;
		}

		memset(buff, '\0', sizeof(buff));
		memset(intBuff, '\0', sizeof(intBuff));

		/* Checking if received something from the clients */
		for (i = 1; i <= maxi; i++) {
			/* If there's no client associated with this index, go ahead */
			if ((listenfd = client[i].fd) < 0)
				continue;

			/* Else check if it is the i client that sent something */
			if (FD_ISSET(listenfd, &rset)) {
				memset(buff, '\0', sizeof(buff));
				/* If it read the EOF, close the connection with that client */
				if ((n = read(listenfd, buff, MAXLINE)) == 0) {
					if (closeMatch(0, &allset, listenfd, intBuff, client, i,
							match, j, "END:Other player surrender. You won!\n",
							"A player surrender. Match finished\n"))
						err_quit("Match closing error\n");
				}
				/* If it read something else, manage it */
				else {
					int temp = -1;
					j = findMatch(match, client, listenfd);

					/* Need to know which client is sending something
					 * of the 2 playing together
					 */
					if (client[match[j].info[0].client].fd == listenfd) {
						temp = 0;
						temp1 = 1;
					} else {
						temp = 1;
						temp1 = 0;
					}

					/* One of the players still need to position his/her ships */
					if ((match[j].info[0].numShips != NUMSHIPS)
							|| (match[j].info[1].numShips != NUMSHIPS)) {
						/* Parsing the received informations
						 * If they are correct, add the ship
						 */
						if (!(parseLineShips(buff, &ship, &k, &l, &m))) {
							/* Need to check if we can add the specified ship */
							if (!(checkShip(ship, match[j].info, temp))) {
								/* Need to check now if the ship can be placed in the specified location */
								if (!(checkShipPlacement(ship, match[j].info,
										temp, k, l, m))) {

									if (match[j].info[temp].numShips != NUMSHIPS) {
										buffShipPlacement(buff, match[j].info,
												temp);
										if (write(
												client[match[j].info[temp].client].fd,
												buff, strlen(buff)) < 0)
											err_sys("write error\n");
									} else {
										if (match[j].info[temp1].numShips
												!= NUMSHIPS) {
											buffGame(buff, match[j].info, temp);
											strcat(buff,
													"Waiting for your opponent\n");
											if (write(
													client[match[j].info[temp].client].fd,
													buff, strlen(buff)) < 0)
												err_sys("write error\n");
										} else {
											for (k = 0; k < 2; k++) {
												buffGame(buff, match[j].info,
														k);
												if (k == match[j].turn)
													strcat(buff,
															"It's your turn\n");
												else
													strcat(buff,
															"Wait, other player turn\n");
												if (write(
														client[match[j].info[k].client].fd,
														buff, strlen(buff)) < 0)
													err_sys("write error\n");
											}
										}
									}

								} else {
									buffShipPlacement(buff, match[j].info,
											temp);
									strcat(buff,
											"The ship can't be placed in that location\n");
									if (write(listenfd, buff, strlen(buff)) < 0)
										err_sys("write error\n");
								}
							} else {
								buffShipPlacement(buff, match[j].info, temp);
								strcat(buff, "Can't add the specified ship\n");
								if (write(listenfd, buff, strlen(buff)) < 0)
									err_sys("write error\n");
							}
						}
						/* If they are incorrect, just notify it */
						else {
							buffShipPlacement(buff, match[j].info, temp);
							strcat(buff, "Wrong syntax\n");
							if (write(listenfd, buff, strlen(buff)) < 0)
								err_sys("write error\n");
						}
					} else {
						/* If it's the right client sending a message then can manage it */
						if ((match[j].turn == 0
								&& listenfd
										== client[match[j].info[0].client].fd)
								|| (match[j].turn == 1
										&& listenfd
												== client[match[j].info[1].client].fd)) {
							if (!(parseLine(buff, &k, &l))) {
								/* The inserted value need to be between 0 and SIDE
								 * or it'll be out of the matrix */
								if ((k < SIDE) && (k >= 0) && (l < SIDE)
										&& (l >= 0)) {
									/* Selecting the right player */
									if (match[j].turn == 0) {
										temp1 = 0;
										temp2 = 1;
									} else {
										temp1 = 1;
										temp2 = 0;
									}

									/* If the selected position is still empty */
									if (match[j].info[temp1].moves[k][l] == 0) {
										/* If the player hit something, notify it */
										if (checkHit(match[j].info, temp1,
												temp2, k, l)) {
											printf(
													"Player %d from match %d used %s, and hit\n",
													match[j].turn + 1, j,
													strtok(buff, "\n"));
										}
										/* Else notify the miss */
										else {
											printf(
													"Player %d from match %d used %s, but missed\n",
													match[j].turn + 1, j,
													strtok(buff, "\n"));
										}
										/* If someone won
										 *
										 *
										 *
										 *
										 *
										 *
										 * */
										if ((m = checkWin(match[j].info))) {
											memset(intBuff, '\0',
													sizeof(intBuff));
											strcat(intBuff, "Match ");
											sprintf(conv, "%d", j);
											strcat(intBuff, conv);
											strcat(intBuff,
													" finished. Player ");
											sprintf(conv, "%d", m);
											strcat(intBuff, conv);
											strcat(intBuff, " won\n");
											if (closeMatch(1, &allset, listenfd,
													buff, client, i, match, j,
													"END:You lost, sorry\n",
													intBuff))
												err_quit(
														"Match closing error\n");
										}
										/* Else, just keep going and pass turn to the other client */
										else {
											if (match[j].turn == 0)
												match[j].turn = 1;
											else
												match[j].turn = 0;

											for (k = 0; k < 2; k++) {
												buffGame(buff, match[j].info,
														k);
												if (k == match[j].turn)
													strcat(buff,
															"It's your turn\n");
												else
													strcat(buff,
															"Wait, other player turn\n");
												if (write(
														client[match[j].info[k].client].fd,
														buff, strlen(buff)) < 0)
													err_sys("write error\n");
											}
										}

									} else {
										buffGame(buff, match[j].info, temp);
										strcat(buff, "Wrong position\n");
										if (write(listenfd, buff, strlen(buff))
												< 0)
											err_sys("write error\n");
									}
								} else {
									buffGame(buff, match[j].info, temp);
									strcat(buff, "Out of matrix\n");
									if (write(listenfd, buff, strlen(buff)) < 0)
										err_sys("write error\n");
								}
							} else {
								buffGame(buff, match[j].info, temp);
								strcat(buff, "Unknown message\n");
								if (write(listenfd, buff, strlen(buff)) < 0)
									err_sys("write error\n");
							}
						} else {
							buffGame(buff, match[j].info, temp);
							strcat(buff, "It's not your turn\n");
							if (write(listenfd, buff, strlen(buff)) < 0)
								err_sys("write error\n");
						}
					}
				}
				if (--ready <= 0)
					break;
			}
		}
	}
	close(client[0].fd);
	exit(0);
}
