#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

void positivi(int vet[], int num)
{
	int *posi=(int *) malloc(num*sizeof(int));
	if(posi==NULL)
	{
		printf("memoria insufficente\n");
		return;
	}
	int conta=0;
	for(int i=0;i<num;i++)
		if(vet[i]>0)
			posi[conta++]=vet[i];
	posi=(int *) realloc(posi,conta*sizeof(int));
	for(int i=0;i<conta;i++)
		printf("%d\n",posi[i]);
	free(posi);
	return;
}

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("inserire più di due valori\n");
		return 1;
	}
	int vet[argc];
	for(int i=0;i<argc;i++)
		vet[i]=atoi(argv[i]);
	positivi(vet,argc);
	return 0;
}

