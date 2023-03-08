#include "basic.h"
#define WAITTIME 120
#define MAXBOTHERING 5

typedef struct list {
	struct sockaddr_in clientAddr;
	int len;
	struct timeval reqTime;
	int count;
	struct list *next;
} listClients;

typedef struct infoRcv {
	char protRcv[10], hostRcv[50], portRcv[5];
} infoRcv;

int parseLine(char input[], infoRcv *info);
int checkClient(struct sockaddr_in cliaddr, socklen_t len,
		struct list **listClients, int *times, long *timeleft);
void clearList(struct list **listClients, struct timeval *now);
void clear(void *obj);
