#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

int *dispari(int vet[],int num,int *k,int *pari)
{
	int *a=(int *) malloc(num*sizeof(int));
	int somma=0,conta=0;
	if(a==NULL)
	{
		printf("poca memoria\n");
		exit(1);
	}
	for(int i=0;i<num;i++)
	{
		if(vet[i]%2==0)
			somma+=vet[i];
		else
			a[conta++]=vet[i];
	}
	a=(int *) realloc(a,conta*sizeof(int));
	*k=conta;
	*pari=somma;
	return a;	
}

int main(int argc,char *argv[])
{
	if(argc<=2)
	{
		printf("inserire più di due valori interi\n");
		return 1;
	}
	int vet[argc-1],siz,totp;
	for(int i=0;i<argc-1;i++)
		vet[i]=atoi(argv[i]);
	int *a=dispari(vet,argc-1,&siz,&totp);
	for(int i=0;i<siz;i++)
		printf("%d\n",a[i]);
	printf("totale numeri dispari:%d\n", siz);
	printf("somma dei numeri pari:%d\n", totp);
	free(a);
	return 0;
}

