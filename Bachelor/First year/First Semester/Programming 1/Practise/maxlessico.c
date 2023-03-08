#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#define dim 100

int main(int argc,char *argv[])
{
	if(argc<=2)
	{
		printf("inserire piu' valori\n");
		return 1;
	}
	char *vet[argc-1];
	char *max[dim];
	for(int i=1;i<=argc;i++)
	{
		if(max[0]<argv[i]);
			max[0]=argv[i];
	}
	printf("%s\n",max[0]);
	return 0;
}

