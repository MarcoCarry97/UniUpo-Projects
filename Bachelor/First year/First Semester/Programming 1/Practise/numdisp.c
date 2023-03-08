#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

int *numdisp(int vet[],int dim,int *disp, int *par)
{
	int *a=(int *) malloc(dim*sizeof(int));
	int totdisp=0;
	int totpari=0;
	for(int i=0;i<dim;i++)
	{
		if(vet[i]%2==1)
			a[totdisp++]=vet[i];
		else
			totpari++;
	}
	a=(int *) realloc(a,totdisp*sizeof(int));
	*disp=totdisp;
	*par=totpari;
	return a;
}

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("inserire solo una stringa ed un valore intero\n");
		return 1;
	}
	int vet[argc-1];
	for(int i=0;i<argc-1;i++)
	{
		vet[i]=atoi(argv[i]);
	}
	int pari=0,dispari=0;
	int *a=numdisp(vet,argc-1,&dispari,&pari);
	for(int i=0;i<dispari;i++)
		printf("%d\n",a[i]);
	free(a);
	printf("numeri dispari:%d\n",dispari);
	printf("numeri pari:%d\n",pari);
	return 0;
}

