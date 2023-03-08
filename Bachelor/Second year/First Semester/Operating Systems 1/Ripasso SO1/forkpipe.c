#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include"xerrors.h"

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("Uso: %s size\n",argv[0]);
		exit(0);
	}
	int size=atoi(argv[1]);
	int *a=random_array(size);
	for(int i=0;i<size;i++)
		a[i]=(int) rand();
	int up[2];
	xpipe(up,__LINE__,__FILE__);
	pid_t pid=xfork(__LINE__,__FILE__);
	if(pid==0)
	{
		int j=0;
		for(int i=0;i<size;i++)
			if(a[i]>=RAND_MAX/2)
				a[j++]=a[i];
		array_sort(a,j);
		assert(check_sort(a,j));
		close(up[1]);
		int e=write(up[0],a,j*sizeof(int));
		if(e==-1)
		{
			perror("Errore scrittura pipe");
			exit(1);
		}
		close(up[0]);
		exit(0);
	}
	int j=0;
	for(int i=0;i<size;i++)
		if(a[i]<RAND_MAX/2)
			a[j++]=a[i];
	array_sort(a,j);
	assert(check_sort(a,j));
	close(up[0]);
	int e=read(up[1],&a[j],j*sizeof(int));
	if(e==-1)
	{
		perror("Errore scrittura pipe");
		exit(1);
	}
	close(up[0]);
	free(a);
	printf("%s\n",check_sort(a,n)) ? "OK" : "ERROR";
	return 0;
}
