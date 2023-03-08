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

typedef struct
{
	int bytesLeft;             // bytes attualmente disponibili
	pthread_cond_t cond;    // condition variable
	pthread_mutex_t mutex;  // mutex associato alla condition variable
}heap;

typedef struct data
{
	int mem;
	int sec;
}data;

int heap_init(heap *h, int maxSize);
int allocate_memory(heap *h, int size);
int free_mem(heap *h, int size);

int tot=0;
volatile bool continua=false;

void handler(int s,data *d, pthread *t)
{
	tot++;
	printf("Segnale %d ricevuto da %d (tot=%d)\n",s,getpid(),tot);
	if(s==SIGUSR1)
	{
		printf("inserire memoria da allocare e tempo da aspettare\n");
		scanf("%d %d",d->mem,d->sec);
		pthread_create(t,NULL, tbody, (void *) d);
	}
}

void *tbody(void *d)
{
	data *var=(data *) d;
	int *a=(int *)malloc(var->mem*sizeof(int));
	assert(a!=NULL);
	pause(var->sec);
	
}

int main()
{
	if(argc!=3)
	{
		printf("Uso: %s tsize memory\n");
	}
	int tsize=atoi(argv[1]), memory=atoi(argv[2]);
	heap h,k;
	heap_init(&h,memory);
	heap_init(&k,memory);
	data d;
	pthread_t t[tsize];
}

int heap_init(heap *h, int maxSize)
{
	byteLeft=maxSize;
	int e=xpthread_cond_init(&h->cond,NULL);
	if(e!=0) return e;
	e=xpthread_mutex_init(&h->mutex,NULL);
	if(e!=0) return e;
	return 0;
}

int allocate_memory(heap *h, int size);
{
	int e=pthread_mutex_lock(&h->mutex);
	if(e!=0) return e;
	while(h->bytesLeft < size)
	{
		e=pthread_cond_wait(&h->cond, &h->mutex);
		if(e!=0) return e;
	}
	h->byteLeft-=size;
	e=pthread_mutex_unlock(&h->mutex);
	if(e!=0) return e;
	return 0;
}

int free_mem(heap *h, int size)
{
	int e=pthread_mutex_lock(&h->mutex);
	if(e!=0) return e;
	h->byteLeft+=size;
	e=pthread_cond_broadcast(&h->cond);
	e=pthread_mutex_unlock(&h->mutex);
	if(e!=0) return e;
	return 0;
}
