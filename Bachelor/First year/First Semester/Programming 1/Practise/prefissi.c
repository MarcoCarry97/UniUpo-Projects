#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#define dim 100

char *prefissi(char stri[])
{
	char *prefis=(char *) malloc(dim*sizeof(int));
	char tot[dim];
	for(int i=0;i<strlen(stri);i++)
	{
		for(int j=0;j<i+1;j++)
		{
			tot[j]=stri[j];
		}
		if(i==0)
			snprintf(prefis,dim,"%s ",tot);
		else
		{
			strncat(prefis,tot,dim);
			snprintf(prefis,dim,"%s ",prefis);
		}
	}
	return prefis;
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("inserire un solo valore\n");
		exit(1);
	}
	char *str=prefissi(argv[1]);
	printf("%s\n",str);
	free(str);
	return 0;
}
