#include "my_functions.h"
#include "list.h"

char* parse(char input[]) {
	char *temp = NULL;
	char copy[MAXLINE];
	memset(copy, '\0', sizeof(MAXLINE));
	strcpy(copy, input);
	if (strtok(copy, "-"))
		if ((temp = strtok(NULL, "\n")))
			return temp;
	return NULL;
}

char* parse_registration(char input[]) {
	char *temp = NULL;
	char copy[MAXLINE];
	memset(copy, '\0', sizeof(MAXLINE));
	strcpy(copy, input);
	if (strtok(copy, "-"))
		if ((strtok(NULL, "-")))
			if ((temp = strtok(NULL, "\n")))
				return temp;
	return NULL;
}

char *remove_new_line(char *name) {
	size_t ln = strlen(name) - 1;
	if (name[ln] == '\n')
		name[ln] = '\0';
	return name;
}

int parseSeverAddr(char input[], char address[], char port[]) {
	char *temp = NULL;
	char copy[MAXLINE];
	memset(copy, '\0', sizeof(MAXLINE));
	strcpy(copy, input);
	if ((strtok(copy, ":")))
		if ((temp = strtok(NULL, "-"))) {
			strcpy(address, temp);
			temp = NULL;
			if ((temp = strtok(NULL, "\n"))) {
				strcpy(port, temp);
				return 0;
			}
		}
	return -1;
}

int parseId(char input[]) {
	char *temp = NULL;
	char copy[MAXLINE];
	memset(copy, '\0', sizeof(MAXLINE));
	strcpy(copy, input);
	if ((temp = strtok(copy, "_")))
		return atoi(temp);
	return -1;
}
