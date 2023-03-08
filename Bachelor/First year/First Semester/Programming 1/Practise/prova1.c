#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 10

int *leggint(char nome[],int *n)
{
	FILE *f=fopen(nome,"r");
	if(f==NULL)
	{
		printf("file non trovato\n");
		*n=-1;
		exit(1);
	}
	int *vet=(int *) malloc(dim*sizeof(int));
	if(vet==NULL)
	{
		printf("memoria insufficiente\n");
		exit(1);
	}
	int i=0;
	char *riga,str[dim];
	while(true)
	{
		riga=fgets(str,dim,f);
		if(riga==NULL)
			break;
		vet[i++]=atoi(str);
	}
	*n=i;
	return vet;
}

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("inserire un solo valore");
		return 1;
	}
	int siz,somma;
	int *vet=leggint(argv[1], &siz);
	for(int i=0;i<siz;i++)
		somma+=vet[i];
	printf("somma=%d\n",somma);
	free(vet);
	return 0;
}

