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
	int num;
	int *buffer;
	int *prodIndex;
	//char *fileName;
	//bool *open;
	FILE *file;
	sem_t *freeSlots;
	sem_t *dataItems;
	pthread_mutex_t *prodMutex;
	pthread_mutex_t *fileMutex;
}data;

void *tbody(void *arg);

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("Uso: %s numThread fileName\n",argv[0]);
		exit(0);
	}
	int numThread=atoi(argv[1]);
	assert(numThread>0);
	int buffer[BUFSIZE];
	int prodIndex=0;
	//bool open=false;
	assert(buffer!=NULL);
	sem_t freeSlots, dataItems;
	xsem_init(&freeSlots,0,BUFSIZE,__LINE__,__FILE__);
	xsem_init(&dataItems,0,0,__LINE__,__FILE__);
	pthread_mutex_t prodMutex, fileMutex;
	xpthread_mutex_init(&prodMutex,NULL,__LINE__,__FILE__);
	xpthread_mutex_init(&fileMutex,NULL,__LINE__,__FILE__);
	pthread_t t[numThread];
	data d[numThread];
	FILE *f=xfopen(argv[2],"r",__LINE__,__FILE__);
	int active=0;
	for(int i=0;i<numThread;i++)
	{
		d[i].num=i;
		d[i].buffer=buffer;
		d[i].prodIndex=&prodIndex;
		//d[i].fileName=argv[2];
		//d[i].open=&open;
		d[i].file=f;
		d[i].freeSlots=&freeSlots;
		d[i].dataItems=&dataItems;
		d[i].prodMutex=&prodMutex;
		d[i].fileMutex=&fileMutex;
		active++;
		xpthread_create(&t[i],NULL,tbody,(void *) &d[i],__LINE__,__FILE__);
	}
	//sleep(5);
	int consIndex=0, sum=0;
	//bool end=false;
	while(active>0)
	{
		xsem_wait(&dataItems,__LINE__,__FILE__);
		int num=buffer[consIndex];
		consIndex=(consIndex+1)%BUFSIZE;
		//printf("il thread principale consuma %d\n",num);
		xsem_post(&freeSlots,__LINE__,__FILE__);
		if(num==-1) active--;
		else sum+=num;
	}
	fclose(f);
	xpthread_mutex_destroy(&prodMutex,__LINE__,__FILE__);
	xpthread_mutex_destroy(&fileMutex,__LINE__,__FILE__);
	printf("Somma dei quadrati con %d thread: %d\n",numThread, sum);
	return 0;
}

void *tbody(void *arg)
{
	data *d=(data *) arg;
	//if(!(*(d->open))) d->file=xfopen(d->fileName,"r",__LINE__,__FILE__);
	bool end=false;
	while(!end)
	{
		xpthread_mutex_lock(d->fileMutex,__LINE__,__FILE__);
		int num;
		fscanf(d->file,"%d",&num);
		xpthread_mutex_unlock(d->fileMutex,__LINE__,__FILE__);
		if(feof(d->file)) end=true;
		else
		{
			xsem_wait(d->freeSlots,__LINE__,__FILE__);
			xpthread_mutex_lock(d->prodMutex,__LINE__,__FILE__);
			//printf("il thread %d produce %d\n",d->num,num);
			d->buffer[(*(d->prodIndex))]=num*num;
			(*(d->prodIndex))=((*(d->prodIndex))+1)%BUFSIZE;
			xpthread_mutex_unlock(d->prodMutex,__LINE__,__FILE__);
			xsem_post(d->dataItems,__LINE__,__FILE__);
		}
	}
	xsem_wait(d->freeSlots,__LINE__,__FILE__);
	xpthread_mutex_lock(d->prodMutex,__LINE__,__FILE__);
	d->buffer[(*(d->prodIndex))]=-1;
	(*(d->prodIndex))=((*(d->prodIndex))+1)%BUFSIZE;
	xpthread_mutex_unlock(d->prodMutex,__LINE__,__FILE__);
	xsem_post(d->dataItems,__LINE__,__FILE__);

	//fclose(d->file);
	//(*(d->open))=false;
	pthread_exit(NULL);
}
