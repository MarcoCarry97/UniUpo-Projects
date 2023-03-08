#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 10

void stampa(int vet[])
{
	for(int i=0;i<dim;i++)
		printf("%d\n",vet[i]);
	return;
}

int main(/*int argc, char *argv[]*/)
{
/*	if(argc!=2)
	{
		printf("inserire solo un numero\n");
		return 1;
	}fgh
	*/
	int k=0,num;
	int vet[dim];
	for(;;)
	{
		printf("inserire numero\n");
		scanf("%d",&num);
		if(num!=0 && k==dim)
		{
			printf("spazio esaurito\n");
			break;
		}
		else if(num!=0 && k<dim)
			vet[k++]=num;
		else if(num==0)
			{
				stampa(vet);
				return 0;
			}
	}
	return 0;
}
