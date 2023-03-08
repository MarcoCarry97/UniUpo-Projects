/*
 * directory_server.c
 *
 *  Created on: 09/mar/2014
 *      Author: Dario Vogogna
 */

#include "basic.h"
#include "list.h"
#include "my_functions.h"
#include "mysql.h"

int main(int argc, char **argv) {
	int servPort, ready, maxd, sockfd, connfd, n;
	char buff[MAXLINE], conv[10];
	struct sockaddr_in servaddr, cliaddr;
	socklen_t clilen;
	list_node *server_list = NULL, *temp = NULL, *client_list = NULL;
	fd_set rset, allset;
	struct timeval now;

	if (argc != 2)
		err_quit("Usage: %s <port>\n", argv[0]);

	servPort = atoi(argv[1]);

	while (servPort < 10000 || servPort > 12000) {
		printf("Insert a port between 10000 and 12000 please\n");
		servPort = atoi(fgets(conv, sizeof(conv), stdin));
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(servPort);

	if (create_users_database())
		err_sys("couldn't create the database");

	if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");

	if (listen(sockfd, LISTENQ) < 0)
		err_sys("lister error");

	FD_ZERO(&allset);
	FD_SET(sockfd, &allset);
	maxd = sockfd;

	while (1) {
		rset = allset;

		if ((ready = select(maxd + 1, &rset, NULL, NULL, NULL)) < 0)
			err_sys("select error\n");

		/* New client connecting */
		if (FD_ISSET(sockfd, &rset)) {
			clilen = sizeof(struct sockaddr_in);
			if ((connfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen))
					< 0)
				err_sys("accept error\n");
			printf("Client information: %s %d\n", inet_ntoa(cliaddr.sin_addr),
					ntohs(cliaddr.sin_port));
			gettimeofday(&now, NULL);
			/* Adding the connected client to the temporary list because we don't know yet if it is a user or a server */
			list_node *new = create_node(connfd, cliaddr, clilen, now);
			if (add(new, &temp))
				err_msg("Could not add the node to the list");

			FD_SET(connfd, &allset);
			if (connfd > maxd)
				maxd = connfd;
			if (--ready <= 0)
				continue;
		}

		/**************************************************************************************/
		/************************************* SERVERS ****************************************/
		/**************************************************************************************/
		list_node *servers = server_list;
		while (servers && ready > 0) {
			if (FD_ISSET(servers->server_fd, &rset)) {
				memset(buff, '\0', sizeof(buff));
				if ((n = read(servers->server_fd, buff, MAXLINE)) > 0) {
					printf("Client %s %d: %s \n",
							inet_ntoa(servers->svrAddr.sin_addr),
							ntohs(servers->svrAddr.sin_port),
							remove_new_line(buff));
				}
				/* A server disconnected */
				else if (n == 0) {
					if (close(servers->server_fd) == -1)
						err_sys("close error\n");
					FD_CLR(servers->server_fd, &allset);
					list_node *copy = servers;
					printf("The server %s %d closed the connection\n",
							inet_ntoa(copy->svrAddr.sin_addr),
							ntohs(copy->svrAddr.sin_port));
					if (del(copy, &server_list))
						err_msg("Could not delete the node");
					servers = server_list;
					continue;
				} else
					err_sys("read error");
				ready--;
			}
			servers = servers->next;
		}

		/**************************************************************************************/
		/************************************* CLIENTS ****************************************/
		/**************************************************************************************/
		list_node *clients = client_list;
		while (clients && ready > 0) {
			if (FD_ISSET(clients->server_fd, &rset)) {
				memset(buff, '\0', sizeof(buff));
				if ((n = read(clients->server_fd, buff, MAXLINE)) > 0) {
					printf("Client %s %d: %s \n",
							inet_ntoa(clients->svrAddr.sin_addr),
							ntohs(clients->svrAddr.sin_port),
							remove_new_line(buff));

					/* The client sent if it wants to register or login */
					if (strstr(buff, CLIENT_LOGIN_REGISTRATION)) {
						if (parse(buff)) {
							int dec = atoi(parse(buff));
							memset(buff, '\0', sizeof(buff));
							/* It wants to login */
							if (dec == 1) {
								if (!strcpy(buff, WELCOME_CLIENT_USERNAME))
									return -1;
							}
							/* It wants to register */
							else if (dec == 2) {
								if (!strcpy(buff,
								CLIENT_REGISTRATION_USERNAME))
									return -1;
							}
							/* It didn't insert 1 or 2 */
							else {
								if (!strcpy(buff,
								UNKNOWN_MESSAGE_LOGIN_REGISTRATION))
									return -1;
							}
							if ((write(clients->server_fd, buff, strlen(buff)))
									!= strlen(buff))
								err_sys("write error");
						}
					}
					/* Login, the client string contains "login-..." */
					else if (strstr(buff, CLIENT_LOGIN)) {
						/* The client is sending the username, "login-username-..." */
						if (strstr(buff, CLIENT_USERNAME)) {
							strcpy(clients->add_info->username,
									parse_registration(buff));
							memset(buff, '\0', sizeof(buff));
							if (!strcpy(buff, WELCOME_CLIENT_PASSWORD))
								return -1;
						}
						/* The client is sending the password, "login-password-..." */
						else if (strstr(buff, CLIENT_PASSWORD)) {
							strcpy(clients->add_info->password,
									parse_registration(buff));
							memset(buff, '\0', sizeof(buff));
							/* The client logged in correctly, passing him informations of a server */
							if (!check_login(clients)) {
								if (server_list) {
									memset(conv, '\0', sizeof(conv));
									sprintf(conv, "%d",
											clients->add_info->logged);
									if (!strcpy(buff, conv))
										return -1;
									if (!strcat(buff, "_"))
										return -1;
									if (!strcat(buff, WELCOME_CLIENT_LOGGED))
										return -1;
									sprintf(conv, "%d",
											server_list->portNumber);
									printf(
											"Passing the client %s %d information of the first server in the list: %s %s\n",
											inet_ntoa(
													clients->svrAddr.sin_addr),
											ntohs(clients->svrAddr.sin_port),
											inet_ntoa(
													server_list->svrAddr.sin_addr),
											conv);
									strcat(buff,
											inet_ntoa(
													server_list->svrAddr.sin_addr));
									strcat(buff, "-");
									strcat(buff, conv);
									strcat(buff, "\n");
								} else {
									if (!strcpy(buff, NO_SERVERS))
										return -1;
								}
							}
							/* Wrong login informations */
							else {
								if (!strcpy(buff,
								WELCOME_CLIENT_WRONG_LOGIN))
									return -1;
							}
						}
						if ((write(clients->server_fd, buff, strlen(buff)))
								!= strlen(buff))
							err_sys("write error");
					}
					/* A client needs the ip of another server to connect to */
					else if (strcmp(buff, RELOGGING) == 0) {
						memset(buff, '\0', sizeof(buff));
						if (clients->add_info->logged == 1) {
							if (server_list) {
								if (!strcpy(buff, RELOGGED))
									return -1;
								sprintf(conv, "%d", server_list->portNumber);
								printf(
										"Passing the client %s %d information of the first server in the list: %s %s\n",
										inet_ntoa(clients->svrAddr.sin_addr),
										ntohs(clients->svrAddr.sin_port),
										inet_ntoa(
												server_list->svrAddr.sin_addr),
										conv);
								strcat(buff,
										inet_ntoa(
												server_list->svrAddr.sin_addr));
								strcat(buff, "-");
								strcat(buff, conv);
								strcat(buff, "\n");
							} else {
								if (!strcpy(buff, NO_MORE_SERVERS))
									return -1;
							}
						}
						if ((write(clients->server_fd, buff, strlen(buff)))
								!= strlen(buff))
							err_sys("write error");
					}
					/* Registration, the client string contains "registration-..." */
					else if (strstr(buff, NEW_CLIENT_REGISTRATION)) {
						/* The client string contains "registration-username-..." */
						if (strstr(buff, CLIENT_USERNAME)) {
							/* Copy the username inserted to the client struct */
							if (!strcpy(clients->add_info->username,
									parse_registration(buff)))
								return -1;
							/* Notify the client to insert the password now */
							if (!strcpy(buff,
							NEW_CLIENT_REGISTRATION_PASSWORD))
								return -1;
						}
						/* The client string contains "registration-password-..." */
						else if (strstr(buff, CLIENT_PASSWORD)) {
							/* Copy the password inserted to the client struct */
							if (!strcpy(clients->add_info->password,
									parse_registration(buff)))
								return -1;
							/* Notify the client to re-insert the password */
							if (!strcpy(buff,
							NEW_CLIENT_REGISTRATION_PASSWORD_REPEAT))
								return -1;
						}
						/* The client string contains "registration-password_confirm-..." */
						else if (strstr(buff, CLIENT_PASSWORD_CONFIRM)) {
							/* If the user repeated the password correctly */
							if (strcmp(clients->add_info->password,
									parse_registration(buff)) == 0) {
								/* Gonna check if an user with the same name already exists, or i'll add this new one */
								if (registrer_new_user(clients)) {
									printf(
											"Username already present in the database\n");
									if (!strcpy(buff,
									NEW_CLIENT_REGISTRATION_ERROR_PRESENT))
										return -1;
								} else {
									printf("Registered new user %s\n",
											clients->add_info->username);
									if (!strcpy(buff,
									NEW_CLIENT_REGISTRATION_COMPLETE))
										return -1;
								}
							}
							/* Else he didn't repeat the password correctly, going back to the main menu */
							else {
								/* Reset username and password in the struct */
								if (add_client_info(clients))
									return -1;
								/* And go back to main menu */
								if (!strcpy(buff,
								NEW_CLIENT_REGISTRATION_ERROR))
									return -1;
							}
						}
						if ((write(clients->server_fd, buff, strlen(buff)))
								!= strlen(buff))
							err_sys("write error");
					}
					/* Client is closing the connection */
					else if (strstr(buff, GOODBYE_OK)) {
						if (close(clients->server_fd) == -1)
							err_sys("close error\n");
						FD_CLR(clients->server_fd, &allset);
						list_node *copy = clients;
						clients = clients->next;
						printf("The client %s %d closed the connection\n",
								inet_ntoa(copy->svrAddr.sin_addr),
								ntohs(copy->svrAddr.sin_port));
						if (del(copy, &client_list))
							err_msg("Could not delete the node");
						clients = client_list;
					}
					/* Unknown message */
					else {
						memset(buff, '\0', sizeof(buff));
						if (!strcpy(buff, UNKNOWN_MESSAGE))
							return -1;
						if ((write(clients->server_fd, buff, strlen(buff)))
								!= strlen(buff))
							err_sys("write error");
					}
				}
				/* A client disconnected */
				else if (n == 0) {
					if (close(clients->server_fd) == -1)
						err_sys("close error\n");
					FD_CLR(clients->server_fd, &allset);
					list_node *copy = clients;
					clients = clients->next;
					printf("The client %s %d closed the connection\n",
							inet_ntoa(copy->svrAddr.sin_addr),
							ntohs(copy->svrAddr.sin_port));
					if (del(copy, &client_list))
						err_msg("Could not delete the node");
					clients = client_list;
					continue;
				} else
					err_sys("read error");

				ready--;
			}
			clients = clients->next;
		}

		/* Checking all connected temporary clients */
		list_node **lista = &temp;
		while ((*lista) && ready > 0) {
			if (FD_ISSET((*lista)->server_fd, &rset)) {
				memset(buff, '\0', sizeof(buff));
				if ((n = read((*lista)->server_fd, buff, MAXLINE)) > 0) {
					/* If it is a server connecting, then it would use a fixed string */
					if (strstr(buff, NEW_SERVER_STRING)) {
						/* Adding the new server to the server list */
						int port = 0;
						if (!(port = atoi(parse(buff))))
							return -1;
						printf(
								"New server connected and added to server list: %s %d\n",
								inet_ntoa((*lista)->svrAddr.sin_addr), port);
						memset(buff, '\0', sizeof(buff));
						if (!strcpy(buff, ADD_SERVER_STRING_OK))
							return -1;
						if ((write((*lista)->server_fd, buff, strlen(buff)))
								!= strlen(buff))
							err_sys("write error");
						if (move(lista, &server_list, (*lista), port))
							err_msg("Could not move the node");
					}
					/* Same thing if a new client is connecting */
					else if (strcmp(buff, NEW_CLIENT_STRING) == 0) {
						printf(
								"New client connected and added to client list: %s %d\n",
								inet_ntoa((*lista)->svrAddr.sin_addr),
								ntohs((*lista)->svrAddr.sin_port));
						memset(buff, '\0', sizeof(buff));
						if (!strcpy(buff, WELCOME_CLIENT))
							return -1;
						if ((write((*lista)->server_fd, buff, strlen(buff)))
								!= strlen(buff))
							err_sys("write error");
						if (move(lista, &client_list, (*lista), 0))
							err_msg("Could not move the node");
						if (add_client_info(client_list))
							err_msg("The node had already info assigned");
					}
				}
				/* A client disconnected */
				else if (n == 0) {
					if (close((*lista)->server_fd) == -1)
						err_sys("close error\n");
					FD_CLR((*lista)->server_fd, &allset);
					list_node *copy = (*lista);
					(*lista) = (*lista)->next;
					if (del(copy, lista))
						err_msg("Could not delete the node");
				} else
					err_sys("read error");

				ready--;
			} else
				(*lista) = (*lista)->next;
		}
	}
	close(sockfd);
}
