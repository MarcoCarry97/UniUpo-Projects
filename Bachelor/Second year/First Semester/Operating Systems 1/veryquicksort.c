#define _GNU_SOURCE
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>  
#include <assert.h>

#define Buf_size 10

typedef struct{
	int p;
	int r;
} elem;

typedef struct {
  elem *buffer; 
  int *ar;
  int *cindex;
  pthread_mutex_t *mutex_consumers;
  sem_t *sem_free_slots;
  sem_t *sem_data_items;  
} dati;

int *random_array(int n, int seed);
int *copy_array(int *a, int n);
bool check_sort(int *a, int *b, int n);
int intcmp(const void *a, const void *b);
void *tbody(void *arg);
void quicksort(int *A, int p, int r);
int partition(int A[], int p, int r);
void very_quicksort(int *arr,int p,int r, int numel, int limit, elem *buf, int pindex);

// funzione eseguita dai thread consumer
void *tbody(void *arg)
{  
  dati *a = (dati *)arg;
  while(true) {
	puts("thread consumer eseguito");
    int e = sem_wait(a->sem_data_items);
    assert(e==0);
    pthread_mutex_lock(a->mutex_consumers);
    elem n = a->buffer[*(a->cindex)];
    int p = n.p;
    int r = n.r;
    *(a->cindex) = (*(a->cindex) + 1) % Buf_size;
    pthread_mutex_unlock(a->mutex_consumers);
    e = sem_post(a->sem_free_slots);
    assert(e==0);
    if(p<0 && r<0) break;
    quicksort(a->ar,p,r);
  }
  pthread_exit(NULL); 
}    

int main(int argc, char **argv)
{
	if(argc > 5 || argc < 4)
		{
			printf("Numero erraro di argomenti\n");
			puts("Uso: numel numthread limite [seed]");
			return 1;
		}
	// inizializzazioni
	int n, p, limit, seed, e, i;
	n = atoi(argv[1]);
	assert(n>0);
	p = atoi(argv[2]);
	assert(p>0);
	limit = atoi(argv[3]);
	if(argc==5)
		seed = atol(argv[4]);
	else
		seed = 3141562;
	int *arr = (int *)malloc(n*sizeof(int));
	int *copia = (int *)malloc(n*sizeof(int));
	arr = random_array(n, seed);
	
	//for(int j=0; j<n; j++)
		//printf("%d\n", arr[j]);
		
	// crea una copia dell'array ordinata con qsort
	copia = copy_array(arr,n);
	qsort(copia,n,sizeof(int), intcmp);
	
	// inizializzazioni per i thread/semafori
	elem buffer[Buf_size];
	int cindex=0, pindex=0;
	pthread_t t[p];
	dati a[p];
	sem_t sem_free_slots, sem_data_items;
	pthread_mutex_t mutex_consumers = PTHREAD_MUTEX_INITIALIZER;
 
	// inizializzazione semafori
	e = sem_init(&sem_free_slots, 0, Buf_size);
	assert(e==0);
	e = sem_init(&sem_data_items, 0, 0);
	assert(e==0);
	
	//  creo i thread consumatori
	for(i=0;i<p;i++) 
	{
		a[i].buffer = buffer;
		a[i].cindex = &cindex;
		a[i].mutex_consumers = &mutex_consumers;
		a[i].sem_data_items  = &sem_data_items;
		a[i].sem_free_slots  = &sem_free_slots;
		a[i].ar = arr;
		e = pthread_create(&t[i], NULL, tbody, (void *) &a[i]);
		assert(e==0);
	}
	// chiamo la funzione very_quicksort
	very_quicksort(arr, 0, n-1, n, limit, buffer, pindex);
	
	// segnalo terminazione
	for(int i=0;i<p;i++) 
	{
		e = sem_wait(&sem_free_slots);
		assert(e==0);
		elem tmp;
		tmp.p = -1;
		tmp.r = -1;
		buffer[pindex] = tmp;
		pindex = (pindex+1)%Buf_size;
		e = sem_post(&sem_data_items);
		assert(e==0);
	}
	
	// join dei thread
	for(i=0;i<p;i++) 
	{
		e = pthread_join(t[i], NULL);
		if(e==0) 
			fprintf(stderr,"Thread %d terminato\n",i);
		else 
			fprintf(stderr,"Errore join %d\n",e);
	}
	
	// check ordine array tra arr thread con array qsort
	if(check_sort(arr,copia,n))
		fprintf(stderr,"Sort OK\n");
	else
		fprintf(stderr,"Sorting fallito\n");
	return 0;
}
 
void very_quicksort(int *arr,int p,int r, int numel, int limit, elem *buf, int pindex)
{
  int q = r;
  if(p < r) {
    if(numel <= limit){
      elem item;
      item.p = p;
      item.r = q;
      buf[pindex] = item;
      pindex++;
    }
    else {
      // esegui come nel caso senza thread:
      q =  partition(arr,p,r);
      very_quicksort(arr, p, q, numel, limit, buf, pindex);
      very_quicksort(arr, q+1, r, numel, limit, buf, pindex);
    }
  }
 }

// genera array di n elementi con interi random tra 0 e 999999 
int *random_array(int n, int seed)
{
  assert(n>0);
  srandom(seed);
  int *a = malloc(n* sizeof(int));
  assert(a!=NULL);
  for(int i=0;i<n;i++)
    a[i] = (int) random() % 1000000;
  return a;
}

// crea una copia dell'array a 
int *copy_array(int *a, int n)
{
  int *b = (int *) malloc(n* sizeof(int));
  assert(b!=NULL);
  for(int i=0;i<n;i++)
    b[i] = a[i];
  return b;
}

// verifica che l'array a[0..n] sia uguale a b[0..n]
bool check_sort(int *a, int *b, int n)
{
  for(int i=0;i<n;i++)
     if(a[i]!=b[i]) return false;
  return true;
}

// funzione di confronto tra interi passata a qsort
int intcmp(const void *a, const void *b)
{
  return *((int *) a) - *((int *) b);
}

void quicksort(int *A, int p, int r){
  int q;
  
  if(p<r) {  // se p==r  c'e'un solo elemento e quindi non si deve ordinare
    q = partition(A,p,r);
    quicksort(A,p,q);
    quicksort(A,q+1,r);
  }
}

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
}
