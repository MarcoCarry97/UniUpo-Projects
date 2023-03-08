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
	*x = atoi(temp);
	memset(temp, '\0', sizeof(*temp));
	if (!(temp = strtok(NULL, "\n")))
		return -1;
	*y = atoi(temp);
	return 0;
}

void printGrid(int **matr, char *buff) {
	int i, j;
	char temp[10];
	memset(buff, '\0', sizeof(*buff));
	for (i = 0; i < (SIDE * SQUARE); i++) {
		strcat(buff, "\t");
		for (j = 0; j < (SIDE * SQUARE); j++) {
			if ((i == 0) && ((j % SQUARE) == (SQUARE / 2))) {
				memset(temp, '\0', sizeof(*temp));
				sprintf(temp, " %d ", (j / SQUARE));
				strcat(buff, temp);
			} else if ((j == 0) && (i % SQUARE == (SQUARE / 2))) {
				memset(temp, '\0', sizeof(*temp));
				sprintf(temp, " %d ", (i / SQUARE));
				strcat(buff, temp);
			} else if ((i != 0) && (i % SQUARE == 0)) {
				if (j % SQUARE == 0) {
					if (matr[i / SQUARE][j / SQUARE] == 1)
						printO(i % SQUARE, j % SQUARE, buff);
					else if (matr[i / SQUARE][j / SQUARE] == 2)
						printX(i % SQUARE, j % SQUARE, buff);
					else
						strcat(buff, "   ");
				} else
					strcat(buff, " = ");
			} else {
				if ((j != 0) && (i != 0) && (j % SQUARE == 0))
					strcat(buff, " | ");
				else {
					if (matr[i / SQUARE][j / SQUARE] == 1)
						printO(i % SQUARE, j % SQUARE, buff);
					else if (matr[i / SQUARE][j / SQUARE] == 2)
						printX(i % SQUARE, j % SQUARE, buff);
					else
						strcat(buff, "   ");
				}
			}
		}
		strcat(buff, "\n");
	}
}

void printX(int x, int y, char *buff) {
	if ((y == 2) && (x == 2))
		strcat(buff, "  \\");
	else if ((y == 4) && (x == 2))
		strcat(buff, "/  ");
	else if ((y == 3) && (x == 3))
		strcat(buff, " X ");
	else if ((y == 2) && (x == 4))
		strcat(buff, "  /");
	else if ((y == 4) && (x == 4))
		strcat(buff, "\\  ");
	else
		strcat(buff, "   ");
}

void printO(int x, int y, char *buff) {
	if ((y == 2) && (x == 2))
		strcat(buff, " / ");
	else if ((y == 3) && (x == 2))
		strcat(buff, "---");
	else if ((y == 4) && (x == 2))
		strcat(buff, " \\ ");
	else if (((y == 2) || (y == 4)) && (x == 3))
		strcat(buff, " | ");
	else if ((y == 2) && (x == 4))
		strcat(buff, " \\ ");
	else if ((y == 4) && (x == 4))
		strcat(buff, " / ");
	else if ((y == 3) && (x == 4))
		strcat(buff, "---");
	else
		strcat(buff, "   ");
}

int checkWin(int **matr) {
	/* X X X	- - -	- - -
	 * - - -	X X X	- - -
	 * - - -	- - -	X X X */
	if (((matr[0][0] == 1) && (matr[0][1] == 1) && (matr[0][2] == 1))
			|| ((matr[1][0] == 1) && (matr[1][1] == 1) && (matr[1][2] == 1))
			|| ((matr[2][0] == 1) && (matr[2][1] == 1) && (matr[2][2] == 1)))
		return 1;
	/* X - -	- X -	- - X
	 * X - -	- X -	- - X
	 * X - -	- X -	- - X */
	else if (((matr[0][0] == 1) && (matr[1][0] == 1) && (matr[2][0] == 1))
			|| ((matr[0][1] == 1) && (matr[1][1] == 1) && (matr[2][1] == 1))
			|| ((matr[0][2] == 1) && (matr[1][2] == 1) && (matr[2][2] == 1)))
		return 1;
	/* X - -	- - X
	 * - X -	- X -
	 * - - X	X - - */
	else if (((matr[0][0] == 1) && (matr[1][1] == 1) && (matr[2][2] == 1))
			|| ((matr[2][0] == 1) && (matr[1][1] == 1) && (matr[0][2] == 1)))
		return 1;
	/* O O O	- - -	- - -
	 * - - -	O O O	- - -
	 * - - -	- - -	O O O */
	if (((matr[0][0] == 2) && (matr[0][1] == 2) && (matr[0][2] == 2))
			|| ((matr[1][0] == 2) && (matr[1][1] == 2) && (matr[1][2] == 2))
			|| ((matr[2][0] == 2) && (matr[2][1] == 2) && (matr[2][2] == 2)))
		return 2;
	/* O - -	- O -	- - O
	 * O - -	- O -	- - O
	 * O - -	- O -	- - O */
	else if (((matr[0][0] == 2) && (matr[1][0] == 2) && (matr[2][0] == 2))
			|| ((matr[0][1] == 2) && (matr[1][1] == 2) && (matr[2][1] == 2))
			|| ((matr[0][2] == 2) && (matr[1][2] == 2) && (matr[2][2] == 2)))
		return 2;
	/* O - -	- - O
	 * - O -	- O -
	 * - - O	O - - */
	else if (((matr[0][0] == 2) && (matr[1][1] == 2) && (matr[2][2] == 2))
			|| ((matr[2][0] == 2) && (matr[1][1] == 2) && (matr[0][2] == 2)))
		return 2;
	/* No one won yet */
	else
		return 0;
}

int parseLineCli(char input[]) {
	char *copy;
	copy = (char *) malloc(sizeof(input));
	memset(copy, '\0', sizeof(*copy));
	strcpy(copy, input);
	if (!(strtok(copy, "END")))
		return -1;
	return 0;
}

/* Finding the corresponding match of the client */
int findMatch(matches *match, clients *client, int listenfd) {
	int j;
	for (j = 0; (j < (FD_SETSIZE / 2)); j++) {
		if ((client[match[j].client1].fd == listenfd)
				|| (client[match[j].client2].fd == listenfd))
			return j;
	}
	if (j == (FD_SETSIZE / 2)) {
		err_quit("match not found\n");
		return -1;
	}
	return -1;
}
