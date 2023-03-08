#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

void minmax(int *a, int num,int *mi, int *ma)
{
	int min=a[0],max=a[0]; 
	for(int i=1;i<num;i++)
	{
		if(max<a[i])
			max=a[i];
		else if(min>a[i])
			min=a[i];
	}
	*mi=min;
	*ma=max;
	return;
}

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("inserire più di due valori\n");
		return 1;
	}
	int vet[argc],min,max;
	for(int i=0;i<argc;i++)
		vet[i]=atoi(argv[i]);
	minmax(vet,argc,&min,&max);
	printf("Max=%d  Min=%d\n",max,min);
	return 0;
}

