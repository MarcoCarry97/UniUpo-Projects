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

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("inserire più valori\n");
		return 1;
	}
	int vet[argc-1],max;
	for(int i=0;i<argc;i++)
	{
		vet[i]=atoi(argv[i]);
	}
	max=massimo(vet,argc-1);
	printf("valore massimo:%d\n",max);
	return 0;
}
