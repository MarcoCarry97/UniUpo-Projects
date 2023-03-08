#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<pthread.h>
#include<semaphore.h>

typedef struct heap
{
	int byteLeft;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
}heap;

int heap_init(heap *h, int maxSize);
int allocate_memory(heap *h, int size);
int free_mem(heap *h, int size);
void *tbody(void *arg);

heap h;


int tot=0;
volatile bool cont=true;
void handler(int s)
{
	tot++;
	printf("ricevuto %d da %d\n",s,getpt());
	if(s==SIGUSR1)
	{
		pthread_t t;
		int e=pthread_create(&t,NULL, tbody,NULL);
		assert(e==0);
	}
	else if(s==SIGUSR2) printf("Memoria disponibile: %d\n",h.byteLeft);
	else if(s==SIGINT) cont=false;
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("Uso: %s maxSize\n",argv[0]);
		exit(0);
	}
	int maxSize=atoi(argv[1]);
	int e=heap_init(&h,maxSize);
	assert(e==0);
	struct sigaction sa;
 	sa.sa_handler = handler;
 	sigemptyset(&sa.sa_mask);     
 	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1,&sa,NULL);
	sigaction(SIGUSR2,&sa,NULL);
	sigaction(SIGINT,&sa,NULL);
	printf("processo %d\n",getpid());
	while(cont) pause();
	e=pthread_mutex_destroy(&h.mutex);
	assert(e==0);
	e=pthread_cond_destroy(&h.cond);
	assert(e==0);
	return 0;
}

int heap_init(heap *h, int maxSize)
{
	h->byteLeft=maxSize;
	int e=pthread_cond_init(&h->cond,NULL);
	int f=pthread_mutex_init(&h->mutex,NULL);
	return e+f;
}

int allocate_memory(heap *h, int size)
{
	int e=0, f=0, g=0;
	e=pthread_mutex_lock(&h->mutex);
	while(h->byteLeft<size)
		f= pthread_cond_wait(&h->cond,&h->mutex);
	h->byteLeft-=size;
	g=pthread_mutex_unlock(&h->mutex);
	return e + f + g;
}

int free_mem(heap *h, int size)
{
	int e=0, f=0, g=0;
	e=pthread_mutex_lock(&h->mutex);
	h->byteLeft+=size;
	f=pthread_cond_broadcast(&h->cond);
	g=pthread_mutex_unlock(&h->mutex);
	return e + f + g;
}

void *tbody(void *arg)
{
	int size;
	time_t time;
	printf("Inserire memoria da allocare e tempo d'attesa\n");
	scanf("%d %ld",&size,&time);
	int e=allocate_memory(&h,size);
	//printf("memoria rimasta: %d\n",h.byteLeft);
	assert(e==0);
	sleep(time);
	e=free_mem(&h,size);
	printf("%d blocchi liberati dopo %ld secondi\n",size,time);
	assert(e==0);
	pthread_exit(NULL);
}
