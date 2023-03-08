#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

int *raddoppia(int vet[],int num,int *d)
{
	int *doppi=(int *) malloc(num*sizeof(int));
	int conta=0;
	for(int i=0;i<num;i++)
		if(vet[i]!=0)
			doppi[conta++]=2*vet[i];
	doppi=(int *) realloc(doppi,conta*sizeof(int));
	*d=conta;
	return doppi;
}

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("inserire più di due valori\n");
		return 1;
	}
	int vet[argc-1],dim;
	for(int i=0;i<argc-1;i++)
		vet[i]=atoi(argv[i]);
	int *a=raddoppia(vet,argc-1,&dim);
	for(int i=0;i<dim;i++)
		printf("%d\n",a[i]);
	free(a);
	return 0;
}
