#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 10
int main(int argc, char *argv[])
{   
	if (argc!=1)
	{
		printf("bisogna inserire un solo numero");
		return 1;
	}
	int array[dim],num=atoi(argv[0]),k,conta[2];
	printf("inserire numero k:");
	scanf("%d",&k);
	for(int i=0;i<k;i++)
	{
		printf("inserire numero:");
		scanf("%d",&num);
		array[i]=num;
		if(i==dim)
		{
			printf("spazio finito");
			break;
		}
	}
	for(int i=0;i<=num;i++)
	{
		if(array[i]>1 && array[i]<10)
		conta[0]++;
		else if(array[i]>30 && array[i]<40)
		conta[1]++;
		if(array[i]>5 && array[i]<50)
		conta[2]++;
	}
	printf("numeri tra 1 e 10: %d",conta[0],"\n");
	printf("numeri tra 30 e 40: %d",conta[1],"\n");
	printf("numeri tra 5 e 50: %d",conta[2],"\n");
	return 0;
}	
