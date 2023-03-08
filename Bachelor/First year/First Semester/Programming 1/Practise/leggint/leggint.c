#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

int *leggint(char nome[],int *n)
{
	int dim=20,conta=0;
	FILE *f=fopen(nome,"r");
	if(f==NULL)
	{
		printf("il file non esiste\n");
		*n=-1;
		exit(1);
	}
	int *vet=(int *) malloc(dim*sizeof(int));
	if(vet==NULL)
	{
		printf("memoria insuffieciente\n");
		exit(1);
	}
	char *riga,stri[100];
	while(true)
	{
		riga=fgets(stri,100,f);
		if(riga==NULL)
			break;
		if(conta==dim)
		{
			dim*=2;
			vet=(int *) realloc(vet,dim*sizeof(int));
		}
		vet[conta++]=atoi(stri);
	}
	fclose(f);
	*n=conta;
	vet=(int *) realloc(vet,conta*sizeof(int));
	return vet;
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("inserire un solo valore\n");
		exit(1);
	}
	int dim;
	int *interi=leggint(argv[1],&dim);
	for(int i=0;i<dim;i++)
		printf("%d\n",interi[i]);
	free(interi);
	return 0;
}
