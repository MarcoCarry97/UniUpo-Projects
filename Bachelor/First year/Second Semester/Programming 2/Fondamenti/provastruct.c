#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

typedef struct
{
	char nome;
	char cogn;
	char eta;
}person;

void carica(person vet[], int num)
{
	for(int i=0;i<num;i++)
	{
		printf("Nome %d\n",i);
		scanf("%s",&vet[i].nome);
		printf("Eta' %d\n",i);
		scanf("%d",&vet[i].eta);
	}
	return;
}

int vecchio(person vet[],int num, int *giov)
{
	int max=vet[0].eta, min=vet[0].eta;
	for(int i=1;i<num;i++)
	{
		if(max<vet[i].eta)
			max=vet[i].eta;
		else if(min>vet[i].eta)
			min=vet[i].eta;
	}
	*giov=min;
	return max;
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("inserire solo un valore\n");
		return 1;
	}
	int dim=atoi(argv[1]);
	person A[dim];
	int etag;
	carica(A,dim);
	int etav=vecchio(A,dim,&etag);
	printf("la persona piu' vecchia ha %d anni, la piu' giovane ne ha %d\n",etav,etag);
	return 0;
}
