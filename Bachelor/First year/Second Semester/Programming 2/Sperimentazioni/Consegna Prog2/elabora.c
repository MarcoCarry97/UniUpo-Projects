#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 1000000

void elabora(int num)
{
	int *vet=(int *)malloc(dim*sizeof(int));
	for(int i=0;i<dim;i++)
	{
		vet[i]=&vet[i];
		printf("%d\n",vet[i]);
	}
}

int main()
{

	for(int i=0;i<2*dim;i++)
		elabora(dim);		
	printf("FINITO!\n");
	return 0;
}
