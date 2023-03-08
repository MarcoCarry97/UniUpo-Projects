#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#define dim 100

int *lunghezza(char nome[], int *lung)
{
	int c=10;
	FILE *f=fopen(nome,"r");
	if(f==NULL)
	{
		puts("file non trovato");
		exit(1);		
	}
	int conta=0;
	int *vet=(int *) malloc(c*sizeof(int));
	if(vet==NULL)
	{
		puts("memoria non disponibile");
		exit(1);
	}
	vet[conta]=0;
	char *riga,str[dim];
	while(true)
	{
		if(conta+1==dim)
		{
			c*=2;
			vet=(int *) realloc(vet,c*sizeof(int*));
			if(vet==NULL)
			{
				puts("memoria non disponibile");
				exit(1);
			}
		}
		riga=fgets(str,dim,f);
		if(riga==NULL)
		{
			break;
		}
		vet[conta++]=strlen(str);
	}
	*lung=conta;
	vet=(int *) realloc(vet,conta*sizeof(int));
	fclose(f);
	return vet;
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("inserire un solo valore\n");
		exit(1);
	}
	int m;
	int *lung=lunghezza(argv[1],&m);
	for(int i=0;i<m;i++)
		printf("%d\n",lung[i]);
	free(lung);
	return 0;
}
