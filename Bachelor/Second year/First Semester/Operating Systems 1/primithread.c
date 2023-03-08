#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<pthread.h>
#include<semaphore.h>
#include"xerrors.h"

#define BUFSIZE 10

typedef struct data //PARAMETRI DEI THREAD
{
	int idThread;
	int numThread;
	int limit;
	int *buffer;
	int *index;
	sem_t *freeSlots;
	sem_t *dataItems;
	pthread_mutex_t *bufMutex;
}data;

bool primo(int num); //INDICA SE UN NUMERO é PRIMO
void *tbody(void *arg); //CODICE DEI THREAD

int main(int argc, char *argv[])
{
	if(argc!=4) //CONTROLLO INPUT RIGA DI COMANDO
	{
		printf("Uso: %s fileName limit numThread\n",argv[0]);
		exit(0);
	}
	int limit=atoi(argv[2]), numThread=atoi(argv[3]);
	sem_t freeSlots, dataItems;
	int buffer[BUFSIZE];
	int prodIndex=0;
	xsem_init(&freeSlots,0,BUFSIZE,__LINE__,__FILE__); //INDICA #CELLE LIBERE
	xsem_init(&dataItems,0,0,__LINE__,__FILE__); //INDICA #CELLE PIENE
	pthread_mutex_t bufMutex; //PERMETTE LA MUTUA ESCLUSIONE PER I THREAD
	xpthread_mutex_init(&bufMutex,NULL,__LINE__,__FILE__);
	pthread_t t[numThread];
	data d[numThread];
	int active=0; //INDICA #THREAD ATTIVI
	for(int i=0;i<numThread;i++) //CREAZIONE THREAD
	{
		d[i].idThread=i;
		d[i].numThread=numThread;
		d[i].limit=limit;
		d[i].buffer=buffer;
		d[i].index=&prodIndex;
		d[i].freeSlots=&freeSlots;
		d[i].dataItems=&dataItems;
		d[i].bufMutex=&bufMutex;
		xpthread_create(&t[i],NULL,tbody,(void *) &d[i],__LINE__,__FILE__);
		active++;
	}
	int consIndex=0;
	FILE *out=xfopen(argv[1],"w",__LINE__,__FILE__);
	while(active>0) //CONSUMO FINCHé CI SONO THREAD ATTIVI
	{
		int num=0;
		xsem_wait(&dataItems,__LINE__,__FILE__);
		//xpthread_mutex_lock(&bufMutex,__LINE__,__FILE__);
		num=buffer[consIndex];
		consIndex=(consIndex+1)%BUFSIZE;
		//xpthread_mutex_unlock(&bufMutex,__LINE__,__FILE__);
		xsem_post(&freeSlots,__LINE__,__FILE__);
		if(num==-1) active--;
		else fprintf(out,"%d\n",num);
	}
	fclose(out);
	xpthread_mutex_destroy(&bufMutex,__LINE__,__FILE__);
	return 0;
}

bool primo(int n)
{
  	if(n<2) return false;
  	if(n%2==0)
	{
    		if(n==2) return true;
    		else return false;
  	}
  	for (int i=3; i*i<=n; i += 2)
      		if(n%i==0) return false;
  	return true;
}

void *tbody(void *arg)
{
	data *d=(data *) arg;
	int begin=2*d->idThread+1, inc=2*d->numThread;
	//printf("begin %d limit %d inc %d\n",begin,d->limit,inc);
	for(int i=begin;i<d->limit;i+=inc) //INIZIO PRODUZIONE
		if(primo(i))
		{
			xsem_wait(d->freeSlots,__LINE__,__FILE__);
			xpthread_mutex_lock(d->bufMutex,__LINE__,__FILE__);
			d->buffer[(*(d->index))]=i;
			(*(d->index))=((*(d->index))+1)%BUFSIZE;
			xpthread_mutex_unlock(d->bufMutex,__LINE__,__FILE__);
			xsem_post(d->dataItems,__LINE__,__FILE__);
		}
	xsem_wait(d->freeSlots,__LINE__,__FILE__); //SEGNALO TERMINE
	xpthread_mutex_lock(d->bufMutex,__LINE__,__FILE__);
	d->buffer[(*(d->index))]=-1;
	(*(d->index))=((*(d->index))+1)%BUFSIZE;
	xpthread_mutex_unlock(d->bufMutex,__LINE__,__FILE__);
	xsem_post(d->dataItems,__LINE__,__FILE__);
	pthread_exit(NULL);
}
