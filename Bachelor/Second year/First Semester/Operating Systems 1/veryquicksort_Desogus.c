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
#define BUFFERSIZE 10

typedef struct coppia{
	int x,y;
} coppia;

typedef struct dato{
	int *cindex;
	coppia *buffer;
	int *vettore;
	sem_t *sem_r;
	sem_t *sem_w;
	pthread_mutex_t *mutex_buffer;
	pthread_mutex_t *mutex_nrimasti;
	volatile int *nrimasti;
} dato;

void printVett(int A[], int n){
	for (int i=0; i<n; i++){
		printf("A[%d]: %d\n", i, A[i]);
	}
}

// prototipo quicksort e partition 
void quicksort(int a[], int, int );
int partition(int A[], int p, int r);

void *tbody(void *arg){
	dato *a = (dato*)arg;
	while(1){
		int e = sem_wait(a->sem_r);
		assert(e==0);
		pthread_mutex_lock(a->mutex_buffer);
		coppia temp = a->buffer[*(a->cindex)];
		//printf("Leggo coppia: %d e %d in posizione %d\n", temp.x,temp.y,*(a->cindex));
		*(a->cindex) = ((*(a->cindex))+1)%BUFFERSIZE;
		pthread_mutex_unlock(a->mutex_buffer);
		sem_post(a->sem_w);
		if((temp.x <0)&&(temp.y<0)) break;
		quicksort(a->vettore, temp.x, temp.y);
		int da_togliere=((temp.y-temp.x)+1);
		pthread_mutex_lock(a->mutex_nrimasti);
		*(a->nrimasti)-=da_togliere;
		pthread_mutex_unlock(a->mutex_nrimasti);
		//printf("Rimossi %d elementi\n", da_togliere);
		printf("Rimasti %d elementi\n",(*(a->nrimasti)));
	}
	pthread_exit(NULL);
}


void very_quicksort(int A[],int p,int r, int limite, coppia buffer[], int *pindex, sem_t *sem_r, sem_t *sem_w, pthread_mutex_t *mutex_buffer){
	if(p <= r) {
		if (((r-p)+1) <= limite) {
			coppia c;
			c.x = p;
			c.y = r;
			int e = sem_wait(sem_w);
			assert (e==0);
			e = pthread_mutex_lock(mutex_buffer);
			assert(e==0);
			buffer[*pindex]=c;
			printf("Scrivo sul buffer la coppia %d %d in posizione %d\n", c.x, c.y, *pindex);
			*pindex=(*pindex+1)%BUFFERSIZE;
			e = pthread_mutex_unlock(mutex_buffer);
			assert(e==0);
			e = sem_post(sem_r);
			assert(e==0);
		}
		else {
      // esegui come nel caso senza thread:
			int q =  partition(A,p,r);
			//printf("Richiamo veryquick su %d, %d e %d, %d\n", p,q,q+1,r);
			very_quicksort(A,p,q,limite,buffer,pindex,sem_r,sem_w,mutex_buffer);
			very_quicksort(A,q+1,r,limite,buffer,pindex,sem_r,sem_w,mutex_buffer);
		}
	}
}

// genera array di n elementi con interi random tra 0 e 999999 
int *random_array(int n, int seed) {
	assert(n>0);
	srandom(seed);
	int *a = malloc(n* sizeof(int));
	assert(a!=NULL);
	for(int i=0;i<n;i++) a[i] = (int) random() % 1000000;
	return a;
}

// crea una copia dell'array a 
int *copy_array(int *a, int n) {
	int *b = (int *) malloc(n* sizeof(int));
	assert(b!=NULL);
	for(int i=0;i<n;i++) b[i] = a[i];
	return b;
}

// verifica che l'array a[0..n] sia uguale a b[0..n]
bool check_sort(int *a, int *b, int n) {
	for(int i=0;i<n;i++) if(a[i]!=b[i]) return false;
	return true;
}

// funzione di confronto tra interi passata a qsort
int intcmp(const void *a, const void *b) {
	return *((int *) a) - *((int *) b);
}

int main(int argc, char *argv[]) {
	
	int n, seed;
	volatile int nrimasti;
	if((argc<4)||(argc>5)) {
		fprintf(stderr,"USO:  %s numel [seed]\n\n",argv[0]);
		exit(1);
	}
	nrimasti = n = atoi(argv[1]);
	if(n<1) {
		fprintf(stderr,"Input non valido (main)\n");
		exit(1);
	}
	// ----------- legge il seme per i numeri casuali ----------- 
	int nthread = atoi(argv[2]);
	int limite = atoi(argv[3]);
	if(argc==5) seed = atoi(argv[4]);
	else seed = 3141562;
  // genera array random
	int *a = random_array(n,seed);
  // copia array e ordina la copia usando la funzione di libreria
	int *copia = copy_array(a,n);
	qsort(copia,n,sizeof(int), intcmp);
  
  // eseguo il mio algoritmo di ordinamento
	coppia buffer[BUFFERSIZE];
	dato d[nthread];
	pthread_t t[nthread];
	pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t mutex_nrimasti = PTHREAD_MUTEX_INITIALIZER;
	sem_t sem_w, sem_r;
	sem_init(&sem_w,0,BUFFERSIZE);
	sem_init(&sem_r,0,0);
	int pindex = 0;
	int cindex = 0;
	for (int i=0; i<nthread; i++){
		d[i].buffer = buffer;
		d[i].cindex = &cindex;
		d[i].vettore = a;
		d[i].sem_r = &sem_r;
		d[i].sem_w = &sem_w;
		d[i].mutex_buffer = &mutex_buffer;
		d[i].mutex_nrimasti = &mutex_nrimasti;
		d[i].nrimasti = &nrimasti;
		pthread_create(&t[i], NULL, tbody, (void*)&d[i]);
	}
	very_quicksort(a,0,n-1,limite,buffer,&pindex, &sem_r, &sem_w, &mutex_buffer);
	while(nrimasti>0);
	for (int i=0; i<nthread;i++){
		printf("Provo a terminare il thread %d\n",i);
		sem_wait(&sem_w);
		pthread_mutex_lock(&mutex_buffer);
		coppia c;
		c.x = -1;
		c.y = -1;
		buffer[pindex] = c;
		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&sem_r);
		pindex = (pindex+1)%BUFFERSIZE;
	}
	for(int i=0; i<nthread; i++){
		pthread_join(t[i], NULL);
		printf("Terminato il thread %d\n",i);
	}
  //sleep(10);
  // confronto a[] ordinato da me con copia[]
	if(check_sort(a,copia,n)) fprintf(stderr,"Sort OK\n");
	else{
		fprintf(stderr,"Sorting fallito\n");
		printVett(a,n);
	}
	free(a);
	free(copia);
	return 0;
}

// Quicksort: ordina A[p]...A[r] (p<=r)
// il numero di elementi totale da ordinare e' 1+r-p
void quicksort(int *A, int p, int r) {
	int q;
	if(p<r) {  // se p==r  c'e'un solo elemento e quindi non si deve ordinare
		q = partition(A,p,r);
		quicksort(A,p,q);
		quicksort(A,q+1,r);
	}
}

/* ***********************************************************
   partition con scelta pivot mediano di 3 
   per evitare l'uso di random che e' lenta e non thread safe
   *********************************************************** */ 
int partition(int A[], int p, int r) {
	int t,x;
	int i,j;
  // il pivot sara' il mediano tra A[p],A[i],A[r]
	i = (p+r)/2;
	//printf("p: %d, r: %d, pivot: %d\n", p,r,i);
	if( A[p] > A[i] ) {
		t=A[i];
		A[i]=A[p];
		A[p]=t;
	} // scambia A[i]<->A[p] 
	if( A[p] > A[r] ) {
		t=A[r];
		A[r]=A[p];
		A[p]=t;
	} // scambia A[r]<->A[p], ora A[p] e' il minino
	if( A[i] > A[r] ) {
		t=A[r];
		A[r]=A[i];
		A[i]=t;
	} // scambia A[r]<->A[i], ora A[p]<= A[i] <= A[r]
	x = A[i];                   // pivot
	t=A[i];A[i]=A[p];A[p]=t;    // scambia A[i]<->A[p]      
	i= p-1; j= r+1;
	while(1) {
		while(A[--j]>x) ; // scan da destra a sinistra: esce se A[j]<=x
		while(A[++i]<x) ; // scan da sinistra a destra: esce se A[i]>=x
		if(i<j) {         
			t=A[i];
			A[i]=A[j];
			A[j]=t;  // scambia A[i] <-> A[j] e riprendi scansioni
		}
    else break;       // se i>=j termina
	} 
	return j;
}
