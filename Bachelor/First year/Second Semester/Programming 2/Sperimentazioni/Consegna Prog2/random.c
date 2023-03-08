#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 1000000

int *random(int num)
{
	int *vet=(int *)malloc(num*sizeof(int));
	for(int i=0;i<num;i++)
		vet[i]=(rand()%101);
	return vet;
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("inserire un solo valore inter\n");
		return 1;
	}
	int *vet=random(atoi(argv[1]));
	for(int i=0;i<atoi(argv[1]);i++)
		printf("valore: %d - posizione: %p\n",vet[i],&vet[i]);
	return 0;
}
