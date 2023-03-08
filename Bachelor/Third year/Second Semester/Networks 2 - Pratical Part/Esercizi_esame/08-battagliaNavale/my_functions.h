#include "basic.h"

#define SIDE 10
#define SQUARE 2

/* Total spaces used by ships */
#define NUMSHIPS 5
/* How big is a battleship */
#define BATTLESHIP 4
/* Number of battleships */
#define NUMBATTLESHIPS 0
/* How big is a submarine */
#define SUBMARINE 3
/* Number of submarines */
#define NUMSUBMARINES 1
/* How big is a corvette */
#define CORVETTE 2
/* Number of corvettes */
#define NUMCORVETTES 1
/* How big is a lance */
#define LANCE 1
/* Number of lances */
#define NUMLANCES 0

typedef struct clients {
	int fd;
	/* Index of the opponent client in the clients struct */
	int playingWith;
} clients;

typedef struct MoSh {
	int client;
	int **moves;
	/* Number of hits of the opponent ships */
	int hits;
	int **ships;
	/* Number of the total ships */
	int numShips;
	/* Number of ships */
	int battleships;
	int submarines;
	int corvettes;
	int lances;
} MoSh;

typedef struct matches {
	MoSh info[2];
	int turn;
} matches;

int parseLine(char input[], int *x, int *y);
int parseLineShips(char input[], char *ship, int *x, int *y, int *z);
int checkShip(char ship, MoSh *info, int i);
int checkShipPlacement(char ship, MoSh *info, int i, int x, int y, int z);
void buffShipPlacement(char *buff, MoSh *info, int i);
void buffGame(char *buff, MoSh *info, int i);
void printGrid(int **matr, char *buff);
int checkHit(MoSh *info, int player1, int player2, int x, int y);
int findMatch(matches *match, clients *client, int listenfd);
int checkWin(MoSh *info);
int closeMatch(int end, fd_set *allset, int listenfd, char *intBuff,
		clients *client, int i, matches *match, int j, char *notify,
		char *print);
char posLetter(int i);
int posNumber(char i);
