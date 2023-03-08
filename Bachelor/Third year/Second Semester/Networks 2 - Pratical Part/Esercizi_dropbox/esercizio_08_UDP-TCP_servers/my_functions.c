#include	"basic.h"
#include    "my_functions.h"

int parseLine(char input[], infoRcv *info) {
	char *temp;
	char *copy;
	temp = (char *) malloc(100 * sizeof(char));
	copy = (char*) malloc(sizeof(input));
	strcpy(copy, input);
	clear(temp);
	if (!(temp = strtok(copy, ":")))
		return -1;
	strcpy(info->hostRcv, temp);
	clear(temp);
	if (!(temp = strtok(NULL, "\n")))
		return -1;
	strcpy(info->portRcv, temp);
	return 0;
}

int checkClient(struct sockaddr_in cliaddr, socklen_t len,
		struct list **listClients, int *times, long *timeleft) {
	struct list *l, *last;
	struct timeval now;
	gettimeofday(&now, NULL);
	clearList(listClients, &now);
	if (!(*listClients)) {
		if (!((*listClients) = (struct list *) malloc(sizeof(struct list))))
			err_sys("malloc error\n");
		(*listClients)->clientAddr = cliaddr;
		(*listClients)->len = len;
		(*listClients)->reqTime = now;
		(*listClients)->count = *times = 0;
		(*listClients)->next = NULL;
		timeleft = NULL;
		return 0;
	}
	l = *listClients;
	while (l) {
		last = l;
		if ((len == l->len)
				&& (memcmp(&(cliaddr.sin_addr), &(l->clientAddr.sin_addr),
						sizeof(cliaddr.sin_addr)) == 0)) {
			long et_sec = now.tv_sec - (l->reqTime).tv_sec;
			if (et_sec < WAITTIME) {
				*times = ++(l->count);
				*timeleft = (long) WAITTIME - et_sec;
				return -1;
			}
		}
		l = l->next;
	}
	if (!(l = (struct list *) malloc(sizeof(struct list))))
		err_sys("malloc error\n");
	l->clientAddr = cliaddr;
	l->len = len;
	l->reqTime = now;
	l->count = *times = 0;
	l->next = NULL;
	timeleft = NULL;
	last->next = l;
	return 0;
}

void clearList(struct list **listClients, struct timeval *now) {
	struct list *l, *p;
	int same = 1;
	while (*listClients && same) {
		if ((now->tv_sec - ((*listClients)->reqTime).tv_sec) >= WAITTIME) {
			p = *listClients;
			*listClients = (*listClients)->next;
			free(p);
		} else
			same = 0;
	}
	if (*listClients) {
		l = *listClients;
		while (l->next) {
			if ((now->tv_sec - (l->next->reqTime).tv_sec) >= WAITTIME) {
				p = l->next;
				l->next = l->next->next;
				free(p);
			} else
				l = l->next;
		}
	}
}

void clear(void *obj) {
	memset(obj, '\0', sizeof(obj));
}
