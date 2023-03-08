#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 10

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
	int vet[argc-1],num,conta;
	for(int i=0;i<argc;i++)
	{
		vet[i]=atoi(argv[i]);
	}
	printf("inserire numero\n");
	scanf("%d",&num);
	conta=quanti(vet,argc-1,num);
	if(conta>=2)
		printf("%d e' presente 2 o piu' volte all'interno dell'array", num);
	else
		printf("%d,e' presente solo una volta oppure non c'e'",num);
	return 0;
}
