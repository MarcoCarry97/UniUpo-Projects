#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 15
void contatore(int vet[],int min,int max)
{
	int conta=0;
	for(int i=0;i<=dim;i++)
	{
		if(vet[i]>min && vet[i]<max)
		conta++;
	}
	printf("numeri tra %d\n e %d\n: %d\n",min,max,conta);
}
void contatore(int vet[],int min,int max);
int main(int argc,char *argv[])
{
	if(argc!=1)
	{
		printf("bisogna mettere solo un valore in ingresso");
		return 1;
	}
	else
	{
		int array[dim],num,kont;
		printf("inserire valore:");
		scanf("%d",&kont);
		for(int i=0;i<=kont;i++)
		{
			printf("inserire numero:"); //riempie l'array di numeri
			scanf("%d",&num);
			array[i]=num;
		}
		contatore(array[3],1,10);
		contatore(array[3],30,40);
		contatore(array[3],5,50);
		return 0;
	}
}
