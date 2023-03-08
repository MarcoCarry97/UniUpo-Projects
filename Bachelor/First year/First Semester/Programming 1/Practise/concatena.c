#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#define dim 100

int main(int argc,char *argv[])
{
	if(argc<=2)
	{
		printf("inserire un solo valore\n");
		return 1;
	}
	char str[dim];
	//snprintf(str,dim,"%s",str);
	for(int i=1;i<argc;i++)
	{
		snprintf(str,dim,"%s",str);
		snprintf(str,dim,"%s-%s",str,argv[i]);
		//printf("%s",str);
	}
	printf("%s\n",str);
	return 0;
}

