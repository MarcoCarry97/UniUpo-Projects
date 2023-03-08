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
	int shmid=xshmget(IPC_PRIVATE,size*sizeof(int),0600,__LINE__,__FILE__);
	int *shm=xshmat(shmid,NULL,0,__LINE__,__FILE__);
	pid_t pid=xfork(__LINE__,__FILE__);
	if(pid==0)
	{
		int j=0;
		for(int i=0;i<size;i++)
			if(a[i]>=RAND_MAX/2)
				shm[size-1-j++]=a[i];
		array_sort(&shm[size-j],j);
		assert(check_sort(&shm[size-j-1],j));
		exit(0);
	}
	int j=0;
	for(int i=0;i<size;i++)
		if(a[i]<RAND_MAX/2)
			shm[j++]=a[i];
	array_sort(shm,j);
	assert(check_sort(shm,j));
	pid=xwait(NULL,__LINE__,__FILE__);
	//for(int i=0;i<size;i++) printf("%d\n",shm[i]);
	check_sort(shm,size) ? printf("OK\n") : printf("ERROR\n");
	free(a);
	xshmdt(shm,__LINE__,__FILE__);
	xshmctl(shmid,IPC_RMID,NULL,__LINE__,__FILE__);
	return 0;
}
