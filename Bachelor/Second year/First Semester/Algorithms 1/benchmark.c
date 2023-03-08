#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define MAX 100

/*clock_t T1, T2;
T1= clock();
... richiamo il mio algoritmo
T2= clock();
double tempoDiEsecuzione= (double)(T2 –T1)/CLOCKS_PER_SEC;*/

void swap(int *a, int *b){
	int *c;
	c=b;
	b=a;
	a=c;
}

void bubblesort(int a[], int n){
	int ult=n-1;
	int ultemp;
	int scambiati=1;
	int i;
	while(scambiati>0){
		scambiati=0;
		for(i=0; i<ult;i++){
			if (a[i]>a[i+1]){
				swap(&a[i], &a[i+1]);
				ultemp=i;
				scambiati=1;

			}

	}
	ult=ultemp;

}
int partition(int array[], int begin, int end) {
    int pivot, l, r, random;
    pivot = array[begin];
    l = begin + 1;
    r = end;
    while(l <= r) {
        while(array[r] > pivot) r=r-1;
        while((array[l] <= pivot) && (l <= r)) l=l+1;
        if (l<r) {
            swap (&array[l], &array[r]);l++;r--;
            }
    }
    swap (&array[begin], &array[r]);
    return r;
}

void quicksort(int array[], int begin, int end) {
    int q;
    if (begin<end) {
        q= partition(array, begin, end);
        quicksort(array, begin, q-1);
        quicksort(array, q+1, end);
        }
}

int left(int i){
    return 2*i+1;
}
int right(int i){
    return 2*i+2;
}

void fixheap(int a[], int i, int heap){

    int l=left(i);
    int r=right(i);
    int big;
    if ((l<heap) && (a[l]<a[i])){
        big=l;
    }
    else{
        big=i;
    }
    if((r<heap)&&(a[r]>a[big])){
            big=r;
    }
    if(big!=i){
        swap(&a[i], &a[big]);
        fixheap(a,i,heap);
    }
}

void Heapify(int a [], int n){
    for(i=n/2;i=0;i--){
        fixheap(a,i,n);
    }
}

void heapsort(int a[],  int n){
    int heap=n;
    heapify(a, n);
    for(i=n-1;i>=0;i--){
        swap(&a[0], &a[i]);
        heap=heap-1;
        fixheap(a,0,heap);
    }
}


int creaArrayRandom (int n) {
    int*arr= (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
            arr[i] = rand() % MAX;
    }
    return arr;
}

int copiarray(int *inputarray, int n){
    int *arr=(int*)malloc(n * sizeof(int));
    memcpy(arr,inputarray,n*sizeof(int));
    return arr;
}

int main(){
    int *array;
    int begin,end;
    int k;
	int N=10;
	int dimensioni[]={5,10,25,50,100,200,500,1000,2000};
	for (i=0;lenght(dimensioni);i++){
        n=dimensioni[i];
        int timebubble,timequick,timeheap=0;
        for(k=1;k<N;k++){
            int *inputarray=creaArrayRandom(n);
            int *arraycopy=copiarray(inputarray,n);
            //int T1=currentime();
            bubblesort(a, n);
            //int T2=currentime();
            //timebubble=timebubble+(T2-T1);
            free (arraycopy);
            int *arraycopy1=copiarray(inputarray,n);
            //int T1=currentime();
            quicksort(array, begin, end);
            //int T2=currentime();
            //timequick=timequick+(T2-T1);
            free (arraycopy1);
            int *arraycopy2=copiarray(inputarray,n);
            //int T1=currentime();
            heapsort(a, n);
            //int T2=currentime();
            //timeheap=timeheap+(T2-T1);
            free (arraycopy2);

        }
	}



    //printf("risultati medi %d, %d, %d",timeBubble/n, timeQuick/n, timeHeap/n)


	return 0;
}
