#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>

void sommamedia(int a[], int b,int *add,float *med)
{
	int sum=0;
	for(int i=0;i<b;i++)
		sum+=a[i];
	*med=sum/b;
	*add=sum;
}

int main()
{
	int num;
	printf("inserire il numero di elementi (massimo 10):");
	scanf("%d",&num);
	int vet[num];
	for(int i=0;i<num;i++)
	{
		printf("inserire valore %d nell'array:",i);
		scanf("%d",&vet[i]);
		//printf("vet %d\n",vet[i]);
	}
	int somma=0;
	float media=0;
	sommamedia(vet,num,&somma,&media);
	printf("Somma: %d\n",somma);
	printf("Media: %.2f\n",media);
	return 0;
}
