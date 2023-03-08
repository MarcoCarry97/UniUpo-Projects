#include "basic.h"
#include "my_functions.h"

int main(int argc, char **argv) {
	/* Sockets variables */
	int sockfd, connfd, listenfd;
	/* System variables */
	int servPort, maxi, maxd, ready;
	/* Temporary variables */
	int i, j, k, l, n, p, temp1, temp2;
	/* Buffers */
	char buff[MAXLINE], intBuff[MAXLINE], conv[10];

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
		match[i].client1 = -1;
		match[i].client2 = -1;
		match[i].turn = -1;
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
				if (match[j].client1 == -1) {
					match[j].client1 = i;
					break;
				}
				/* Creating a new match, setting the first turn randomly */
				else if (match[j].client2 == -1) {
					match[j].client2 = i;

					/* Index of the opponent client */
					client[match[j].client1].playingWith = match[j].client2;
					client[match[j].client2].playingWith = match[j].client1;

					/* Deciding turn randomly */
					srand(time(NULL));
					match[j].turn = rand() % 2;

					/* Matrix initialized to 0, the start of the game */
					match[j].matr = (int **) malloc(SIDE * sizeof(int *));
					for (k = 0; k < SIDE; k++)
						match[j].matr[k] = (int *) calloc(SIDE, sizeof(int));
					for (k = 0; k < SIDE; k++)
						for (l = 0; l < SIDE; l++)
							match[j].matr[k][l] = 0;

					/* Creating the grid in the buffer */
					printGrid(match[j].matr, buff);

					/* Choosing which is the starting player */
					if (match[j].turn == 0) {
						temp1 = match[j].client1;
						temp2 = match[j].client2;
					} else {
						temp1 = match[j].client2;
						temp2 = match[j].client1;
					}

					/* Sending the starting grid to both clients */
					memset(intBuff, '\0', sizeof(intBuff));
					strcpy(intBuff, buff);
					strcat(intBuff, "It's your turn\n");
					if (write(client[temp1].fd, intBuff, strlen(intBuff)) < 0)
						err_sys("write error\n");

					memset(intBuff, '\0', sizeof(intBuff));
					strcpy(intBuff, buff);
					strcat(intBuff, "Wait, other player turn\n");
					if (write(client[temp2].fd, intBuff, strlen(intBuff)) < 0)
						err_sys("write error\n");

					printf("Match %d started between clients %d and %d\n", j,
							match[j].client1, match[j].client2);

					/* Found a free match, don't need to keep searching */
					break;
				}
			}

			/* Should never happen since we would have exited for too many clients error */
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

					/* Closing client1 socket */
					if (close(listenfd) == -1)
						err_sys("close error\n");
					FD_CLR(listenfd, &allset);

					/* Sending the client2 a message noticing that client1 surrender */
					memset(intBuff, '\0', sizeof(intBuff));
					strcpy(intBuff, "END:Other player surrender. You won!\n");
					if (write(client[client[i].playingWith].fd, intBuff,
							strlen(intBuff)) < 0)
						err_sys("write error\n");

					/* Closing client2 socket */
					if (close(client[client[i].playingWith].fd) == -1)
						err_sys("close error\n");
					FD_CLR(client[client[i].playingWith].fd, &allset);

					j = findMatch(match, client, listenfd);

					/* Initializing the match structure */
					match[j].client1 = -1;
					match[j].client2 = -1;
					match[j].turn = -1;
					free(*(match[j].matr));
					free(match[j].matr);

					/* Initializing the client structure */
					printf("A player surrender. Match finished\n");
					client[client[i].playingWith].fd = -1;
					client[client[i].playingWith].playingWith = -1;
					client[i].fd = -1;
					client[i].playingWith = -1;
				}
				/* If it read something else, manage it */
				else {

					j = findMatch(match, client, listenfd);

					/* If it's the right client sending a message then can manage it */
					if ((match[j].turn == 0
							&& listenfd == client[match[j].client1].fd)
							|| (match[j].turn == 1
									&& listenfd == client[match[j].client2].fd)) {
						if (!(parseLine(buff, &k, &l))) {
							/* The inserted value need to be between 0 and SIDE
							 * or it'll be out of the matrix */
							if ((k < SIDE) && (k >= 0) && (l < SIDE)
									&& (l >= 0)) {

								/* If the selected position is still empty */
								if (match[j].matr[k][l] == 0) {
									printf("Player %d from match %d used %s",
											match[j].turn + 1, j, buff);
									/* Print the right simbol */
									match[j].matr[k][l] = match[j].turn + 1;
									/* Pass turn to the other client */
									if (match[j].turn == 0)
										match[j].turn = 1;
									else
										match[j].turn = 0;
									/* Send the new grid to both clients */
									printGrid(match[j].matr, buff);
									if (match[j].turn == 0) {
										temp1 = match[j].client1;
										temp2 = match[j].client2;
									} else {
										temp1 = match[j].client2;
										temp2 = match[j].client1;
									}

									/* Check if a player won */
									if ((p = checkWin(match[j].matr)) == 1) {
										/* Sending the winning grid to both clients */
										memset(intBuff, '\0', sizeof(intBuff));
										strcpy(intBuff, buff);
										strcat(intBuff,
												"END:You won! CONGRATULATIONS\n");
										if (write(client[match[j].client1].fd,
												intBuff, strlen(intBuff)) < 0)
											err_sys("write error\n");

										memset(intBuff, '\0', sizeof(intBuff));
										strcpy(intBuff, buff);
										strcat(intBuff,
												"END:You lost! sorry\n");
										if (write(client[match[j].client2].fd,
												intBuff, strlen(intBuff)) < 0)
											err_sys("write error\n");
										/* Closing both connections */
										printf(
												"Match between %d %d finished. Player 1 won. All connections closed\n",
												match[j].client1,
												match[j].client2);
										if (close(client[match[j].client1].fd)
												== -1)
											err_sys("close error\n");
										FD_CLR(client[match[j].client1].fd,
												&allset);
										client[match[j].client1].fd = -1;
										/* And the opponent's client, so the match also */
										if (close(
												client[client[match[j].client1].playingWith].fd)
												== -1)
											err_sys("close error\n");
										FD_CLR(
												client[client[match[j].client1].playingWith].fd,
												&allset);
										client[client[match[j].client1].playingWith].fd =
												-1;
										client[match[j].client1].playingWith =
												-1;
										client[client[match[j].client1].playingWith].playingWith =
												-1;
										match[j].client1 = -1;
										match[j].client2 = -1;
										match[j].turn = -1;
										free(*(match[j].matr));
										free(match[j].matr);
									} else if (p == 2) {
										/* Sending the winning grid to both clients */
										memset(intBuff, '\0', sizeof(intBuff));
										strcpy(intBuff, buff);
										strcat(intBuff,
												"END:You lost! sorry\n");
										if (write(client[match[j].client1].fd,
												intBuff, strlen(intBuff)) < 0)
											err_sys("write error\n");
										memset(intBuff, '\0', sizeof(intBuff));
										strcpy(intBuff, buff);
										strcat(intBuff,
												"END:You won! CONGRATULATIONS\n");
										if (write(client[match[j].client2].fd,
												intBuff, strlen(intBuff)) < 0)
											err_sys("write error\n");
										/* Closing both connections */
										printf(
												"Match between %d %d finished. Player 2 won. All connections closed\n",
												match[j].client1,
												match[j].client2);
										if (close(client[match[j].client1].fd)
												== -1)
											err_sys("close error\n");
										FD_CLR(client[match[j].client1].fd,
												&allset);
										client[match[j].client1].fd = -1;
										/* And the matchenent's client, so the match also */
										if (close(
												client[client[match[j].client1].playingWith].fd)
												== -1)
											err_sys("close error\n");
										FD_CLR(
												client[client[match[j].client1].playingWith].fd,
												&allset);
										client[client[match[j].client1].playingWith].fd =
												-1;
										client[match[j].client1].playingWith =
												-1;
										client[client[match[j].client1].playingWith].playingWith =
												-1;
										match[j].client1 = -1;
										match[j].client2 = -1;
										match[j].turn = -1;
										free(*(match[j].matr));
										free(match[j].matr);
									} else {
										/* Sending the grid to both clients */
										memset(intBuff, '\0', sizeof(intBuff));
										strcpy(intBuff, buff);
										strcat(intBuff, "It's your turn\n");
										if (write(client[temp1].fd, intBuff,
												strlen(intBuff)) < 0)
											err_sys("write error\n");
										memset(intBuff, '\0', sizeof(intBuff));
										strcpy(intBuff, buff);
										strcat(intBuff,
												"Wait, other player's turn\n");
										if (write(client[temp2].fd, intBuff,
												strlen(intBuff)) < 0)
											err_sys("write error\n");
									}
								} else {
									memset(buff, '\0', sizeof(buff));
									strcpy(buff, "Wrong position\n");
									if (write(listenfd, buff, strlen(buff)) < 0)
										err_sys("write error\n");
								}
							} else {
								memset(buff, '\0', sizeof(buff));
								strcpy(buff, "Out of matrix\n");
								if (write(listenfd, buff, strlen(buff)) < 0)
									err_sys("write error\n");
							}
						} else {
							memset(buff, '\0', sizeof(buff));
							strcpy(buff, "Unknown message\n");
							if (write(listenfd, buff, strlen(buff)) < 0)
								err_sys("write error\n");
						}
					} else {
						memset(buff, '\0', sizeof(buff));
						strcpy(buff, "It's not your turn\n");
						if (write(listenfd, buff, strlen(buff)) < 0)
							err_sys("write error\n");
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
