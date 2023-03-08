#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<pthread.h>
#include<semaphore.h>
#include"xerrors.h"

#define BUFSIZE 10

typedef struct data
{
	char *fileName;
	int *buffer;
	int *index;
	sem_t *freeSlots;
	sem_t *dataItems;
	pthread_mutex_t *bufMutex;
}data;

void *tbody(void *arg);
long pot(long x,int y);

int main(int argc, char *argv[])
{
	if(argc!=4)
	{
		printf("Uso: %s fileName numFile numThread\n",argv[0]);
		exit(0);
	}
	int numFile=atoi(argv[2]), numThread=atoi(argv[3]);
	sem_t freeSlots, dataItems;
	pthread_mutex_t bufMutex;
	xsem_init(&freeSlots,0,BUFSIZE,__LINE__,__FILE__);
	xsem_init(&dataItems,0,0,__LINE__,__FILE__);
	xpthread_mutex_init(&bufMutex,NULL,__LINE__,__FILE__);
	int buffer[BUFSIZE];
	int consIndex=0;
	pthread_t t[numThread];
	data d[numThread];
	for(int i=0;i<numThread;i++)
	{
		d[i].fileName=argv[1];
		d[i].buffer=buffer;
		d[i].index=&consIndex;
		d[i].freeSlots=&freeSlots;
		d[i].dataItems=&dataItems;
		d[i].bufMutex=&bufMutex;
		xpthread_create(&t[i],NULL,tbody,(void *) &d[i],__LINE__,__FILE__);
	}
	int prodIndex=0;
	for(int i=1;i<=numFile;i++)
	{
		xsem_wait(&freeSlots,__LINE__,__FILE__);
		buffer[prodIndex]=i;
		prodIndex=(prodIndex+1)%BUFSIZE;
		xsem_post(&dataItems,__LINE__,__FILE__);
	}
	for(int i=0;i<numThread;i++)
	{
		xsem_wait(&freeSlots,__LINE__,__FILE__);
		buffer[prodIndex]=-1;
		prodIndex=(prodIndex+1)%BUFSIZE;
		xsem_post(&dataItems,__LINE__,__FILE__);
	}
	for(int i=0;i<numThread;i++)
	{
		xpthread_join(t[i],NULL,__LINE__,__FILE__);
		printf("thread %d terminato\n",i);
	}
	xpthread_mutex_destroy(&bufMutex,__LINE__,__FILE__);
	return 0;
}

void *tbody(void *arg)
{
	data *d=(data *) arg;
	bool endThread=false;
	while(!endThread)
	{	
		int esp=0;
		xsem_wait(d->dataItems,__LINE__,__FILE__);
		xpthread_mutex_lock(d->bufMutex,__LINE__,__FILE__);
		esp=d->buffer[(*(d->index))];
		(*(d->index))=((*(d->index))+1)%BUFSIZE;
		xpthread_mutex_unlock(d->bufMutex,__LINE__,__FILE__);
		xsem_post(d->freeSlots,__LINE__,__FILE__);
		if(esp==-1) endThread=true;
		else
		{
			long num=0;
			FILE *input=xfopen(d->fileName,"r",__LINE__,__FILE__);
			char outName[100];
			sprintf(outName,"%s.%d",d->fileName,esp);
			FILE *output=xfopen(outName,"w",__LINE__,__FILE__);
			bool endFile=false;
			while(!endFile)
			{
				fscanf(input,"%ld",&num);
				if(feof(input)) endFile=true;
				else fprintf(output,"%ld\n",pot(num,esp));
			}
			fclose(output);
			fclose(input);
		}
	}
	pthread_exit(NULL);
}

long pot(long x,int y)
{
	long ret=1;
	for(int i=0;i<y;i++)
		ret*=x;
	return ret;
}
