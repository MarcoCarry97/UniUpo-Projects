#include	"basic.h"
#include    "my_functions.h"

int parseLine(char input[], int *x, int *y) {
	char *temp;
	char *copy;
	temp = (char *) malloc(100 * sizeof(char));
	copy = (char *) malloc(sizeof(input));
	memset(copy, '\0', sizeof(*copy));
	strcpy(copy, input);
	memset(temp, '\0', sizeof(*temp));
	if (!(temp = strtok(copy, "-")))
		return -1;
	*x = posNumber(temp[0]);
	memset(temp, '\0', sizeof(*temp));
	if (!(temp = strtok(NULL, "\n")))
		return -1;
	*y = (atoi(temp) - 1);
	return 0;
}

int parseLineShips(char input[], char *ship, int *x, int *y, int *z) {
	char *temp;
	char *copy;
	temp = (char *) malloc(100 * sizeof(char));
	copy = (char *) malloc(sizeof(input));
	memset(copy, '\0', sizeof(*copy));
	strcpy(copy, input);
	memset(temp, '\0', sizeof(*temp));
	/* Char of the ship */
	if (!(temp = strtok(copy, " ")))
		return -1;
	*ship = temp[0];
	memset(temp, '\0', sizeof(*temp));
	/* Pos x of the ship */
	if (!(temp = strtok(NULL, "-")))
		return -1;
	*x = posNumber(temp[0]);
	memset(temp, '\0', sizeof(*temp));
	/* Pos y of the ship */
	if (!(temp = strtok(NULL, " ")))
		return -1;
	*y = (atoi(temp) - 1);
	memset(temp, '\0', sizeof(*temp));
	/* Direction */
	if (!(temp = strtok(NULL, "\n")))
		return -1;
	*z = atoi(temp);
	return 0;
}

int checkShip(char ship, MoSh *info, int i) {
	switch (ship) {
	case 'b': {
		if (info[i].battleships == NUMBATTLESHIPS)
			return -1;
		else
			return 0;
	}
	case 'c': {
		if (info[i].corvettes == NUMCORVETTES)
			return -1;
		else
			return 0;
	}
	case 's': {
		if (info[i].submarines == NUMSUBMARINES)
			return -1;
		else
			return 0;
	}
	case 'l': {
		if (info[i].lances == NUMLANCES)
			return -1;
		else
			return 0;
	}
	default:
		return -1;
	}
}

int checkShipPlacement(char ship, MoSh *info, int i, int x, int y, int z) {
	int j;
	/* The placement isn't inside the matrix */
	if ((x < 0) || (x > SIDE) || (y < 0) || (y > SIDE) || (z < 0) || (z > 1))
		return -1;

	/* Now depends on the ship that want to be placed */
	switch (ship) {
	case 'b': {
		if (z == 1) {
			for (j = x; ((j - x) < BATTLESHIP) && (j < SIDE); j++)
				if (info[i].ships[j][y] != 0)
					return -1;
		} else {
			for (j = y; ((j - y) < BATTLESHIP) && (j < SIDE); j++)
				if (info[i].ships[x][j] != 0)
					return -1;
		}
		if ((j > SIDE))
			return -1;
		else {
			if (z == 1) {
				for (j = x; ((j - x) < BATTLESHIP) && (j < SIDE); j++)
					info[i].ships[j][y] = 1;
			} else {
				for (j = y; ((j - y) < BATTLESHIP) && (j < SIDE); j++)
					info[i].ships[x][j] = 1;
			}
			info[i].battleships++;
			info[i].numShips += BATTLESHIP;
			return 0;
		}
	}
	case 'c': {
		if (z == 1) {
			for (j = x; ((j - x) < CORVETTE) && (j < SIDE); j++)
				if (info[i].ships[j][y] != 0)
					return -1;
		} else {
			for (j = y; ((j - y) < CORVETTE) && (j < SIDE); j++)
				if (info[i].ships[x][j] != 0)
					return -1;
		}
		if ((j > SIDE))
			return -1;
		else {
			if (z == 1) {
				for (j = x; ((j - x) < CORVETTE) && (j < SIDE); j++)
					info[i].ships[j][y] = 2;
			} else {
				for (j = y; ((j - y) < CORVETTE) && (j < SIDE); j++)
					info[i].ships[x][j] = 2;
			}
			info[i].corvettes++;
			info[i].numShips += CORVETTE;
			return 0;
		}
	}
	case 's': {
		if (z == 1) {
			for (j = x; ((j - x) < SUBMARINE) && (j < SIDE); j++)
				if (info[i].ships[j][y] != 0)
					return -1;
		} else {
			for (j = y; ((j - y) < SUBMARINE) && (j < SIDE); j++)
				if (info[i].ships[x][j] != 0)
					return -1;
		}
		if ((j > SIDE))
			return -1;
		else {
			if (z == 1) {
				for (j = x; ((j - x) < SUBMARINE) && (j < SIDE); j++)
					info[i].ships[j][y] = 3;
			} else {
				for (j = y; ((j - y) < SUBMARINE) && (j < SIDE); j++)
					info[i].ships[x][j] = 3;
			}
			info[i].submarines++;
			info[i].numShips += SUBMARINE;
			return 0;
		}
	}
	case 'l': {
		if (z == 1) {
			for (j = x; ((j - x) < LANCE) && (j < SIDE); j++)
				if (info[i].ships[j][y] != 0)
					return -1;
		} else {
			for (j = y; ((j - y) < LANCE) && (j < SIDE); j++)
				if (info[i].ships[x][j] != 0)
					return -1;
		}
		if ((j > SIDE))
			return -1;
		else {
			if (z == 1) {
				for (j = x; ((j - x) < LANCE) && (j < SIDE); j++)
					info[i].ships[j][y] = 4;
			} else {
				for (j = y; ((j - y) < LANCE) && (j < SIDE); j++)
					info[i].ships[x][j] = 4;
			}
			info[i].lances++;
			info[i].numShips += LANCE;
			return 0;
		}
	}
	default:
		return -1;
	}
}

/* Need to ask both clients to insert the ships */
void buffShipPlacement(char *buff, MoSh *info, int i) {
	char conv[10];
	buffGame(buff, info, i);
	strcat(buff, "Time to insert the ships\n");
	strcat(buff, "You still need to place: ");
	memset(conv, '\0', sizeof(conv));
	sprintf(conv, " %d ", (NUMBATTLESHIPS - info[i].battleships));
	strcat(buff, conv);
	strcat(buff, "battleship/s, ");
	memset(conv, '\0', sizeof(conv));
	sprintf(conv, " %d ", (NUMSUBMARINES - info[i].submarines));
	strcat(buff, conv);
	strcat(buff, "submarine/s, ");
	memset(conv, '\0', sizeof(conv));
	sprintf(conv, " %d ", (NUMCORVETTES - info[i].corvettes));
	strcat(buff, conv);
	strcat(buff, "corvette/s and ");
	memset(conv, '\0', sizeof(conv));
	sprintf(conv, " %d ", (NUMLANCES - info[i].lances));
	strcat(buff, conv);
	strcat(buff, "lance/s\n");
	strcat(buff,
			"Use the syntax \"ship x-y direction\"\n\twhere ship:(b = battleship,c = corvette,s = submarine,l = lance), x is a letter between a and j, y is a number between 1 and 10, and direction: 0=horizontal, 1=vertical\n");

}

void buffGame(char *buff, MoSh *info, int i) {
	memset(buff, '\0', sizeof(buff));
	/* Creating the grid in the buffer */
	strcat(buff, "\t\t\tCALLED MOVES\n");
	printGrid(info[i].moves, buff);
	strcat(buff, "\n\n\n\t\t\tYOUR FIELD\n");
	printGrid(info[i].ships, buff);
	strcat(buff, "\n\n");
}

void printGrid(int **matr, char *buff) {
	int i, j;
	char temp[10];
	for (i = 0; i < (SIDE * SQUARE); i++) {
		for (j = 0; j < (SIDE * SQUARE); j++) {
			if ((i == 0) && ((j % SQUARE) == (SQUARE / 2))) {
				memset(temp, '\0', sizeof(*temp));
				sprintf(temp, " %d ", ((j / SQUARE) + 1));
				strcat(buff, temp);
			} else if ((j == 0) && (i % SQUARE == (SQUARE / 2))) {
				memset(temp, '\0', sizeof(*temp));
				sprintf(temp, " %c ", posLetter((i / SQUARE)));
				strcat(buff, temp);
			} else if ((i != 0) && (i % SQUARE == 0)) {
				if (j % SQUARE == 0)
					strcat(buff, "   ");
				else
					strcat(buff, " = ");
			} else {
				if ((j != 0) && (i != 0) && (j % SQUARE == 0))
					strcat(buff, " | ");
				else {
					if ((j != 0) && (i != 0) && (j % SQUARE != 0)
							&& (matr[i / SQUARE][j / SQUARE] == 1))
						strcat(buff, " B ");
					else if ((j != 0) && (i != 0) && (j % SQUARE != 0)
							&& (matr[i / SQUARE][j / SQUARE] == 2))
						strcat(buff, " C ");
					else if ((j != 0) && (i != 0) && (j % SQUARE != 0)
							&& (matr[i / SQUARE][j / SQUARE] == 3))
						strcat(buff, " S ");
					else if ((j != 0) && (i != 0) && (j % SQUARE != 0)
							&& (matr[i / SQUARE][j / SQUARE] == 4))
						strcat(buff, " L ");
					else if ((j != 0) && (i != 0) && (j % SQUARE != 0)
							&& (matr[i / SQUARE][j / SQUARE] == 10))
						strcat(buff, " M ");
					else if ((j != 0) && (i != 0) && (j % SQUARE != 0)
							&& (matr[i / SQUARE][j / SQUARE] == 11))
						strcat(buff, " H ");
					else
						strcat(buff, "   ");
				}
			}
		}
		strcat(buff, "\n");
	}
}

int checkHit(MoSh *info, int player1, int player2, int x, int y) {
	if (info[player2].ships[x][y] != 0) {
		info[player2].ships[x][y] = 11;
		info[player1].moves[x][y] = 11;
		info[player1].hits++;
		return 1;
	} else {
		info[player1].moves[x][y] = 10;
		info[player2].ships[x][y] = 10;
		return 0;
	}
}

/* Finding the corresponding match of the client */
int findMatch(matches *match, clients *client, int listenfd) {
	int j;
	for (j = 0; (j < (FD_SETSIZE / 2)); j++) {
		if ((client[match[j].info[0].client].fd == listenfd)
				|| (client[match[j].info[1].client].fd == listenfd))
			return j;
	}
	if (j == (FD_SETSIZE / 2)) {
		err_quit("match not found\n");
		return -1;
	}
	return -1;
}

int checkWin(MoSh *info) {
	if (info[0].hits == info[1].numShips)
		return 1;
	else if (info[1].hits == info[0].numShips)
		return 2;
	else
		return 0;
}

int closeMatch(int end, fd_set *allset, int listenfd, char *intBuff,
		clients *client, int i, matches *match, int j, char *notify,
		char *print) {
	int k;
	if (end) {
		memset(intBuff, '\0', sizeof(intBuff));
		strcpy(intBuff, "END:Congratulations, you won!\n");
		if (write(listenfd, intBuff, strlen(intBuff)) < 0)
			err_sys("write error\n");
	}
	/* Closing client1 socket */
	if (close(listenfd) == -1)
		err_sys("close error\n");
	FD_CLR(listenfd, allset);

	/* Sending the client2 a message noticing that client1 surrender */
	memset(intBuff, '\0', sizeof(intBuff));
	strcpy(intBuff, notify);
	if (write(client[client[i].playingWith].fd, intBuff, strlen(intBuff)) < 0)
		err_sys("write error\n");

	/* Closing client2 socket */
	if (close(client[client[i].playingWith].fd) == -1)
		err_sys("close error\n");
	FD_CLR(client[client[i].playingWith].fd, allset);

	j = findMatch(match, client, listenfd);

	/* Initializing the match structure */
	match[j].turn = -1;
	for (k = 0; k < 2; k++) {
		match[j].info[k].client = -1;
		match[j].info[k].hits = match[j].info[k].numShips =
				match[j].info[k].battleships = match[j].info[k].corvettes =
						match[j].info[k].submarines = match[j].info[k].lances =
								0;
		free(*(match[j].info[k].moves));
		free(match[j].info[k].moves);
		free(*(match[j].info[k].ships));
		free(match[j].info[k].ships);
	}

	/* Initializing the client structure */
	fputs(print, stdout);
	client[client[i].playingWith].fd = -1;
	client[client[i].playingWith].playingWith = -1;
	client[i].fd = -1;
	client[i].playingWith = -1;
	return 0;
}

char posLetter(int i) {
	switch (i) {
	case 0:
		return 'a';
	case 1:
		return 'b';
	case 2:
		return 'c';
	case 3:
		return 'd';
	case 4:
		return 'e';
	case 5:
		return 'f';
	case 6:
		return 'g';
	case 7:
		return 'h';
	case 8:
		return 'i';
	case 9:
		return 'j';
	default:
		return 'z';
	}
}

int posNumber(char i) {
	switch (i) {
	case 'a':
		return 0;
	case 'b':
		return 1;
	case 'c':
		return 2;
	case 'd':
		return 3;
	case 'e':
		return 4;
	case 'f':
		return 5;
	case 'g':
		return 6;
	case 'h':
		return 7;
	case 'i':
		return 8;
	case 'j':
		return 9;
	default:
		return -1;
	}
}
