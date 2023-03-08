#include "basic.h"
#define SIDE 3
#define SQUARE 6
#define CLIENT1SIGN 1
#define CLIENT2SIGN 2

typedef struct clients {
	int fd;
	/* Index of the opponent client in the clients struct */
	int playingWith;
} clients;

typedef struct matches {
	int client1;
	int client2;
	int turn;
	int **matr;
} matches;

int parseLine(char input[], int *x, int *y);
void clear(void *obj);
void printGrid(int **matr, char *buff);
void printX(int x, int y, char *buff);
void printO(int x, int y, char *buff);
int checkWin(int **matr);
int parseLineCli(char input[]);
int findMatch(matches *match, clients *client, int listenfd);
