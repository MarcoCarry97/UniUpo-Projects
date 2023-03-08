#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<pthread.h>
#include"xerrors.h"

typedef struct data
{
	int *a;
	int b;
	int e;
	int limit;
	pthread_mutex_t *partMutex;
}data;

int *randomArray(int size);
void swap(int *a, int *b);
int medium(int a[],int b,int m, int e);
int partition(int a[], int b, int e);
void quickSort(int a[], int b, int e, int limit, pthread_mutex_t *partMutex);
bool checkSort(int a[],int size);
void *tbody(void *arg);

/*// Quicksort: ordina A[p]...A[r] (p<=r)
// il numero di elementi totale da ordinare e' 1+r-p
void quicksort(int *A, int p, int r, int limit, pthread_mutex_t *partMutex)       
{
	int q;
	if(p<r)
	{
		int help=false;	
		pthread_t t;
		xpthread_mutex_lock(partMutex,__LINE__,__FILE__);  // se p==r  c'e'un solo elemento e 			quindi non si deve ordinare
	    	q = partition(A,p,r);
		xpthread_mutex_unlock(partMutex,__LINE__,__FILE__);
		if(r-q>limit)
		{
			printf("ordino con thread\n");
			data d;
			d.a=A;
			d.b=q+1;
			d.e=r;
			d.limit=limit;
			d.partMutex=partMutex;
			xpthread_create(&t,NULL,tbody,(void *) &d,__LINE__,__FILE__);
			help=true;
			quicksort(A,p,q,limit,partMutex);
		}
		else
		{
			printf("ordino normalemente\n");
	    		quicksort(A,p,q,limit,partMutex);
	    		quicksort(A,q+1,r,limit,partMutex);
		}
		if(help)
		{
			xpthread_join(t,NULL,__LINE__,__FILE__);
			printf("thread terminato\n");
		}
	}
}


 ***********************************************************
   partition con scelta pivot mediano di 3 
   per evitare l'uso di random che e' lenta e non thread safe
   *********************************************************** *
int partition(int A[], int p, int r)
{
  int t,x;
  int i,j;

  // il pivot sara' il mediano tra A[p],A[i],A[r]
  i = (p+r)/2;
  if( A[p] > A[i] )
      {t=A[i];A[i]=A[p];A[p]=t;} // scambia A[i]<->A[p] 
  if( A[p] > A[r] )
      {t=A[r];A[r]=A[p];A[p]=t;} // scambia A[r]<->A[p], ora A[p] e' il minino
  if( A[i] > A[r] )
      {t=A[r];A[r]=A[i];A[i]=t;} // scambia A[r]<->A[i], ora A[p]<= A[i] <= A[r]
  
  x = A[i];                   // pivot
  t=A[i];A[i]=A[p];A[p]=t;    // scambia A[i]<->A[p]      

  i= p-1; j= r+1;
  while(1) {
    while(A[--j]>x) ; // scan da destra a sinistra: esce se A[j]<=x
    while(A[++i]<x) ; // scan da sinistra a destra: esce se A[i]>=x
    if(i<j) {         
      t=A[i]; A[i]=A[j]; A[j]=t;  // scambia A[i] <-> A[j] e riprendi scansioni
    }
    else break;       // se i>=j termina
  } 
  return j;
}*/


int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("Uso: %s size limit\n",argv[0]);
		exit(0);
	}	
	int size=atoi(argv[1]), limit=atoi(argv[2]);
	int *a=randomArray(size);
	for(int i=0;i<size;i++) printf("%d ",a[i]);
	printf("\n");
	pthread_mutex_t partMutex;
	xpthread_mutex_init(&partMutex,NULL,__LINE__,__FILE__);
	quickSort(a,0,size-1,limit,&partMutex);
	for(int i=0;i<size;i++) printf("%d ",a[i]);
	checkSort(a,size) ? printf("OK\n") : printf("ERROR\n");
	free(a);
	xpthread_mutex_destroy(&partMutex,__LINE__,__FILE__);
}

int *randomArray(int size)
{
	int *a=(int *)malloc(size*sizeof(int));
	assert(a!=NULL);
	for(int i=0;i<size;i++)
		a[i]=(int) rand()%100;
	return a;
}

void swap(int *a, int *b)
{
	int tmp=(*a);
	(*a)=(*b);
	(*b)=tmp;
}

int medium(int a[],int b,int m,int e)
{
	if(a[b]>a[m]) swap(&a[b],&a[m]);
	if(a[b]>a[e]) swap(&a[b],&a[e]);
	if(a[m]>a[e]) swap(&a[m],&a[e]);
	int x=a[m];
	swap(&a[m],&a[b]);
	return x;
}

int partition(int a[], int b, int e)
{
	int x=medium(a,b,(b+e)/2,e),inf=b,sup=e;
	while(inf<sup)
	{
		while(a[sup]>x) sup--;
		while(a[inf]<x && inf<=sup) inf++;
		if(inf<sup) swap(&a[inf++],&a[sup--]);
	}
	swap(&a[(b+e)/2],&a[sup]);
	return sup;
}

void quickSort(int a[], int b, int e, int limit,pthread_mutex_t *partMutex)
{
	if(b<e)
	{
		bool help=false;
		xpthread_mutex_lock(partMutex,__LINE__,__FILE__);
		int m=partition(a,b,e);
		xpthread_mutex_unlock(partMutex,__LINE__,__FILE__);
		pthread_t t;
		if(e-m>limit)
		{
			data d;
			d.a=a;
			d.b=m+1;
			d.e=e;
			d.limit=limit;
			d.partMutex=partMutex;
			xpthread_create(&t,NULL,tbody,(void *) &d,__LINE__,__FILE__);
			help=true;
			quickSort(a,b,m,limit,partMutex);
		}
		else
		{
			quickSort(a,b,m,limit,partMutex);
			quickSort(a,m+1,e,limit,partMutex);
		}
		if(help)
		{
			xpthread_join(t,NULL,__LINE__,__FILE__);
			printf("thread terminato\n");
		}
	}
}

bool checkSort(int a[], int size)
{
	for(int i=0;i+1<size;i++)
		if(a[i]>a[i+1]) return false;
	return true;
}

void *tbody(void *arg)
{
	data *d=(data *) arg;
	printf("il thread ordina da %d a %d\n",d->b,d->e);
	quickSort(d->a,d->b,d->e,d->limit,d->partMutex);
	for(int i=d->b;i<=d->e;i++) printf("%d ",d->a[i]);
	printf("\n");
	pthread_exit(NULL);
}
