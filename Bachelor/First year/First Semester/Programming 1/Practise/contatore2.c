#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

 /*Leggere n dalla riga di comando,
  successivamente leggere n interi dal terminale e al termine
   stampare quanti degli interi letti erano compresi tra 1 e 10,
    quanti tra 30 e 40, quanti tra 5 e 50.*/

void contatore(int num[],int dim,int min,int max)
{
	int conta=0;
	for(int i=0;i<dim;i++)
	{
		if(num[i]>min && num[i]<max)
			conta++;
	}
	printf("numeri tra %d e %d:%d\n",min,max,conta);
	return;
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("inserisci solo due valori\n");
		return 1;
	}
	int dim=atoi(argv[1]);
	int num[dim];
	for(int i=0;i<atoi(argv[1]);i++)
	{
		printf("inserire valore\n");
		scanf("%d",&num[i]);
	}
	contatore(num,dim,1,10);
	contatore(num,dim,30,40);
	contatore(num,dim,5,50);
	return 0;
}
