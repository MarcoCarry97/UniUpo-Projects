#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<pthread.h>
#include"xerrors.h"

typedef struct data
{
	int *a;
	int size;
	int thread;
	int begin;
	int *max;
	pthread_mutex_t *mutex;
}data;

int maxThread(int a[], int size, int thread);
void *tbody(void *arg);
int *random_array(int n);

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("Uso: %s size thread\n",argv[0]);
		exit(0);
	}
	int size=atoi(argv[1]), thread=atoi(argv[2]);
	int *a=random_array(size);
	int max=maxThread(a,size,thread);
	printf("Numero massimo calcolato con %d thread: %d\n",thread,max);
	return 0;	
}

int maxThread(int a[], int size, int thread)
{
	pthread_t t[thread];
	data d[thread];
	pthread_mutex_t mutex;
	xpthread_mutex_init(&mutex,NULL,__LINE__,__FILE__);
	int max=0;
	for(int i=0;i<thread;i++)
	{
		d[i].a=a;
		d[i].size=size;
		d[i].thread=thread;
		d[i].begin=(2*i+1)%(2*thread);
		d[i].mutex=&mutex;
		d[i].max=&max;
		xpthread_create(&t[i],NULL,tbody, (void *) &d[i],__LINE__,__FILE__);
	}
	for(int i=0;i<thread;i++) xpthread_join(t[i],NULL,__LINE__,__FILE__);
	//int max=d[0].max;
	//for(int i=0;i<thread;i++)
	//	if(max<d[i].max) max=d[i].max;
	xpthread_mutex_destroy(&mutex,__LINE__,__FILE__);
	return max;
}

void *tbody(void *arg)
{
	data *d=(data *) arg;
	for(int i=d->begin;i<d->size;i+=2*d->thread)
	{
		xpthread_mutex_lock(d->mutex,__LINE__,__FILE__);
		int *point=d->max;
		if(d->max==0) (*point)=d->a[i];
		else if((*point)<d->a[i]) (*point)=d->a[i];
		xpthread_mutex_unlock(d->mutex,__LINE__,__FILE__);
	}
	int *point=d->max;
	printf("massimo: %d\n", (*point));
	pthread_exit(NULL);
}

int *random_array(int n)
{
  assert(n>0);
  int *a = malloc(n* sizeof(int));
  assert(a!=NULL);
  for(int i=0; i < n ;i++)
	//a[i] = ((int)rand())%n;
   a[i] = (rand()%200001) - 100000;
  return a;
}
