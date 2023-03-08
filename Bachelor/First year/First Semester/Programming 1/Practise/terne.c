#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

bool controlla(int vet[], int num)
{
	int cand=vet[0];
	for(int i=1;i<num;i++)
		if(cand==vet[i])
			return false;
	return true;
}

int *terne(int vet[],int num,int *k, bool *dive)
{
	int conta=0;
	int *a=(int *) malloc(num*sizeof(int));
	if(a==NULL)
	{
		printf("memoria insufficiente\n");
		exit(1);
	}
	for(int i=0;i<num-3;i++)
	{
		int somma=0;
		for(int j=i;j<i+3;j++)
			somma+=vet[j];
		a[conta++]=somma;
	}
	*k=conta;
	a=(int *) realloc(a,conta *sizeof(int));
	*dive=controlla(a,num);
	return a;
}

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("inserire più di due valori\n");
		return 1;
	}
	bool div;
	int vet[argc-1],k;
	for(int i=1;i<argc-1;i++)
		vet[i-1]=atoi(argv[i]);
	int *a=terne(vet,argc-1,&k,&div);
	for(int i=0;i<k;i++)
		printf("%d\n",a[i]);
	if(div==true)
		printf("i numeri sono diversi\n");
	else
		printf("i numeri non sono diversi\n");
	free(a);
	return 0;
}
