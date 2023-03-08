#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("Uso: %s fileName\n",argv[0]);
		exit(0);
	}
	int sum=0;
	FILE *f=fopen(argv[1],"r");
	assert(f!=NULL);
	while(!feof(f))
	{
		int num;
		fscanf(f,"%d",&num);
		sum+=num*num;
	}
	fclose(f);
	printf("Somma dei quadrati nel file %s: %d\n",argv[0],sum);
	return 0;
}
