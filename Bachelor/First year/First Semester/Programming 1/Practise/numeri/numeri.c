#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 100

void creafile(int num)
{
	char *stri=(char *) malloc(dim*sizeof(char));
	for(int i=1;i<=num;i++)
	{
		snprintf(stri,dim,"numeri.%d.txt",i);
		FILE *f=fopen(stri,"w");
		for(int j=1;j<=i;j++)
			fprintf(f,"%d ",j);
		fclose(f);
	}
	free(stri);
	return;
}

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("inserire un solo valore");
		return 1;
	}
	creafile(atoi(argv[1]));
	return 0;
}
