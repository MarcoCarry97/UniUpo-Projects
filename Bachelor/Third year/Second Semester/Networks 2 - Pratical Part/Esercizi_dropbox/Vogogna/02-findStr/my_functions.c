#include	"basic.h"
#include    "my_functions.h"

int parseLine(char input[], char fp[], char search[]) {
	char *temp;
	char *copy;
	temp = (char *) malloc(100 * sizeof(char));
	copy = (char*) malloc(sizeof(input));
	strcpy(copy, input);
	memset(temp, '\0', sizeof(*temp));
	if (!(temp = strtok(copy, "-")))
		return -1;
	strcpy(search, temp);
	memset(temp, '\0', sizeof(*temp));
	if (!(temp = strtok(NULL, "\n")))
		return -1;
	strcpy(fp, temp);
	return 0;
}
