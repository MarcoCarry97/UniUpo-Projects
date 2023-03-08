#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 1000

typedef struct data
{
	int sum;
	sem *freeSlots;
	sem *dataItems;
	int ***buffer;
	int size;
}

void *tbody(void *arg)
{
	data d=(data *) (*arg);
	
}

int main(int argc, char *argv[])
{
	if(argc!=4)
	{
		printf("Uso: %s fileName bsize numt\n");
		exit(1);
	}
	int bsize=atoi(argv[2]), numt=atoi(argv[3]);
	assert(bsize>0 && numt>0);
	int **buffer[SIZE];
	p_thread_t t[numt];
	data d[numt];
	sem freeSlots;
	int e=sem_init(&freeSLots,0,SIZE);
	asset(e!=-1);
	sem dataItems;
	e=sem_init(&dataItems,0,0);
	asset(e!=-1);
	FILE *f=fopen(argv[0],"r");
	assert(f!=NULL);
	for(int i=0;i<numt;i++)
	{
		d[i].sum=0;
		d[i].freeSlots=&freeSlots;
		d[i].dataItems=&dataItems;
		d[i].buffer=&buffer;
		d[i].size=bsize;
		pthread_create(t[i],NULL, tbody, (void *)d[i]);
	}
	boolean end=false;
	int i=0;
	int sum=0;
	while(!end)
	{
		int *block=(int *)malloc(sizeof(int);
		assert(block!=NULL);
		int e=fread(block,1,bsize*sizeof(int),f);
		assert(e!=-1);
		if(e<bsize*sizeof(int))
		{
			sum+=(*block);
			free(block);
			end=true;
		}
		else
		{
			buffer[i++]=&block;
			e=sem_post(&dataItems);
			assert(e!=-1);
			e=sem_wait(&freeSlots);
			assert(e!=-1);
		}
	}
	for(int i=0;i<numT;i++)
		pthread_join(t[i],NULL);
	for(int i=0;i<numT;i++)
		sum+=d[i].sum;
	printf("Somma dei numeri: %d\n",sum);
	return 0;
}
