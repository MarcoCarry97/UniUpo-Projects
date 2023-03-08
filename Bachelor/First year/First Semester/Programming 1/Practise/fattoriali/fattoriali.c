#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 100

int fattoriale(int num)
{
	int fatt=1;
	for(int i=1;i<=num;i++)
		fatt*=i;
	return fatt;
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("inserire un solo valore\n");
		return 1;
	}
	char nome[dim];
	snprintf(nome,dim,"fattoriali.%d.txt",atoi(argv[1]));
	FILE *f=fopen(nome,"w");
	for(int i=1;i<=atoi(argv[1]);i++)
	{
		int fatt=fattoriale(i);
		fprintf(f,"%d\n",fatt);
	}
	fclose(f);
	return 0;
}
