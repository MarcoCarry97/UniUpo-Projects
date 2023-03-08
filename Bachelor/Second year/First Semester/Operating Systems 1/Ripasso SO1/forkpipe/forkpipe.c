#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include"xerrors.h"

int *random_array(int n)
{
  assert(n>0);
  int *a = malloc(n* sizeof(int));
  assert(a!=NULL);
  for(int i=0;i < n;i++)
    a[i] = (int) rand();
  return a;
}

int intcmp(const void *a, const void *b)
{
  return *((int *) a) - *((int *) b);
}
// esegue il sort dell'array a[0..n] utilizzando la funzione di libreria qsort
void array_sort(int *a, int n)
{
  qsort(a,n,sizeof(int), intcmp);
}

bool check_sort(int *a, int n)
{
  for(int i=0; i < n-1; i++)
     if(a[i] > a[i+1]) return false;
  return true;
}

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
		close(up[0]);
		int e=write(up[1],a,j*sizeof(int));
		if(e==-1)
		{
			perror("Errore scrittura pipe");
			exit(1);
		}
		close(up[1]);
		exit(0);
	}
	int j=0;
	for(int i=0;i<size;i++)
		if(a[i]<RAND_MAX/2)
			a[j++]=a[i];
	array_sort(a,j);
	assert(check_sort(a,j));
	close(up[1]);
	int e=read(up[0],&a[j],(size-j)*sizeof(int));
	if(e==-1)
	{
		perror("Errore lettura pipe");
		exit(1);
	}
	close(up[0]);
	//for(int i=0;i<size;i++) printf("%d\n",a[i]);
	check_sort(a,size) ? printf("OK\n") : printf("ERROR\n");
	free(a);
	return 0;
}
