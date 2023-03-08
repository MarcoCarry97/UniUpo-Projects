#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

char primo(int num)
{
	if(num<2)
		return false;
	else if(num%2==0)
	{
		if(num==2)
			return true;
		else
			return false;
	}
	else
	{
		for(int i=3;i<num;i=i+2)
			if(num%i==0)
				return false;
	}
	return true;
}

void sommaprimi(int vet[],int dim)
{
	for(int j=0;j<=dim;j++)
		for(int i=0;i<=dim;i++)
		{
			if(vet[i]!=0 || vet[j]!=0)
			{
			int somma=vet[i]+ vet[j];
			if(primo(somma))
				printf("%d (%d+%d)\n",somma,vet[i],vet[j]);
			}
		}
	return;
}

int main(int argc,char *argv[])
{
	if(argc<=2)
	{
		printf("inserire piu' valori\n");
		return 1;
	}
	int vet[argc-1];
	for(int i=1;i<argc-1;i++)
		vet[i]=atoi(argv[i]);
	sommaprimi(vet,argc-1);
	return 0;
}

