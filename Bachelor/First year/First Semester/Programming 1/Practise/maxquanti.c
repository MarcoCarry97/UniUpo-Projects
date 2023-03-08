#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 10

int massimo(int a[], int num)
{
	int max=a[0];
	for(int i=1;i<num;i++)
	{
		if(max<a[i])
			max=a[i];
	}
	return max;
}

int quanti(int a[], int num, int k)
{
	int conta=0;
	for(int i=0;i<num;i++)
	{
		if(k==a[i])
			conta++;
	}
	return conta;
}

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("inserire solo un numero\n");
		return 1;
	}
	int vet[dim],max,conta,a[dim],k=0;
	for(int i=0;i<argc-1;i++)
	{
		vet[i]=atoi(argv[i]); 
	}
	for(int i=0;i<=argc-1;i++)
	{
		conta=quanti(vet,argc-1,vet[i]);
		if(conta>=2)
			a[k++]=vet[i];
	}
	max=massimo(a,k);
	printf("%d e' il valore massimo che si ripete piu' di due volte",max);
	return 0;
}
