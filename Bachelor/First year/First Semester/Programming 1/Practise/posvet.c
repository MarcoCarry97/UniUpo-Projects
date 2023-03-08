#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 10

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("inserire solo un numero\n");
		return 1;
	}
	int *vet=(int *)malloc(dim*sizeof(int));
	int conta=0;
	for(int i=0;i<argc-1;i++)
	{
		if(atoi(argv[i])>0)
		{
		vet[conta]=atoi(argv[0]);
		printf("%d\n",vet[conta]);
		conta++;
		}
	}
	vet=(int *)realloc(vet,conta*sizeof(int));
	return 0;
}
