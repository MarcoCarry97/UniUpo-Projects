#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include <string.h>

#define RUN 10

int *randomArray(int n)
{
    //printf("creazione array\n");
    int *arr = (int *)malloc(n*sizeof(int));
    //printf("bene\n");
    for(int i=0; i<n; i++)
        arr[i] =  (int )rand() % 100000;
    return arr;
}

int *copyArray(int *inputArray, int n)
{
    //printf("copia array\n");
    int *arr = (int *)malloc(n*sizeof(int));
    //printf("bene\n");
    memcpy(arr, inputArray, n*sizeof(int));
    return arr;
}


void swap(int *a,int *b)
{
    int tmp=(*a);
    (*a)=(*b);
    (*b)=tmp;
}

int partition(int array[], int begin, int end)
{
    int pivot, l, r;
    pivot = array[begin];
    l = begin + 1;
    r = end;
    while(l <= r)
    {
        while(array[r] > pivot)
            r = r-1;
        while((array[r] <= pivot) && (l <= r))
            l = l+1;
        if(l < r)
        {
            swap(&(array[l]), &(array[r]));
            l++;
            r--;
        }
    }
    swap(&(array[begin]), &(array[r]));
    return r;
}

void quicksort(int array[], int begin, int end)
{
    int q;
    if (begin<end)
    {
        q= partition(array, begin, end);
        quicksort(array, begin, q-1);
        quicksort(array, q+1, end);
    }
}

int left(int i)
{
    return 2*i+1;
}

int right(int i)
{
    return 2*i+1;
}

int parent(int i)
{
    return (i-1)/2;
}

void fixHeap(int A[], int i, int HeapSize)
{
    int l = left(i);
    int r = right(i);
    int largest = 0;
    if((l < HeapSize) && (A[l] < A[i]))
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if((r < HeapSize) && (A[r] > A[largest]))
    {
        largest = r;
    }
    if(largest != i)
    {
        swap(&A[i], &A[largest]);
        fixHeap(A, largest, HeapSize);
    }
}

void Heapify(int A[], int ArraySize)
{
    for(int i=0; i< (ArraySize/2); i++)
    {
        fixHeap(A, i, ArraySize);
    }
}

void HeapSort(int A[], int ArraySize)
{
    int HeapSize = ArraySize;

    Heapify(A, ArraySize);
    for(int i=1; i< ArraySize-1; i++)
    {
        swap(&A[0], &A[i]);
        HeapSize--;
        fixHeap(A, 0, HeapSize);
    }
}

void BubbleSort(int A[], int n)
{
        int last = n-1;
        int tmp;
        int swapped = 1;
        while( swapped > 0)
        {
            swapped = 0;
            for(int i=0; i< last-1; i++)
            {
                if(A[i] > A[i+1])
                {
                    swap(&A[i], &A[i+1]);
                    tmp = i;
                    swapped = 1;
                }
            }
            last = tmp;
        }
}

bool checksort(int *a, /*int *b,*/ int n)
{
  /*for(int i=0;i<n;i++)
     if(a[i]!=b[i]) return false;
  return true;*/
  for(int i=0;i+1<n;i++)
    if(a[i]>a[i+1]) return false;
  return true;
}

int intcmp(const void *a, const void *b)
{
  return *((int *) a) - *((int *) b);
}

int main()
{
    FILE *f = fopen("ris.csw", "w");
    if(f==NULL)
    {
        perror("Errore apertura file");
        return 0;
    }
    clock_t t1, t2;
    double timeQuick, timeBubble, timeHeap;
    int n;
    int *dim=(int *)malloc(10*sizeof(int));
    if(dim==NULL)
    {
        perror("Errore allocazione\n");
        return 0;
    }
    dim[0]=10;
    for(int i=1;i<10;i++) dim[i]=dim[i-1]*2;
    //printf("ciclo 1\n");
    for(int i=0; i<10; i++)
    {
        n = dim[i];
        timeQuick = 0;
        timeBubble = 0;
        timeHeap = 0;
        int *testArray;
        //printf("ciclo 2-%d\n",i);
        for(int k=0; k<RUN; k++)
        {
            printf("-----------------------------\n");
            testArray = randomArray(n);
            //int *ArrayOrd = copyArray(testArray, n);
            //qsort(ArrayOrd, n ,sizeof(int), intcmp);
            int *ArrayCopy = copyArray(testArray,n);
            //printf("copia 1\n");
            t1 = clock();
            BubbleSort(ArrayCopy, n);
            t2 = clock();
            if(n == 20){
                puts("Bubble");
                for(int y=0; y<20; y++)
                    printf("%d\n", ArrayCopy[y]);
            }
            if(checksort(ArrayCopy, n))
                puts("ok");
            else
                puts("no 1");
            free(ArrayCopy);
            //printf("LIBERTà 1\n");
            double execTime = (double)(t2-t1) / CLOCKS_PER_SEC;
            timeBubble += execTime;

            ArrayCopy = copyArray(testArray,n);
            //printf("copia 2\n");
            t1 = clock();
            quicksort(ArrayCopy,0, n);
            t2 = clock();
             if(n == 20){
                puts("Quick");
                for(int y=0; y<20; y++)
                    printf("%d\n", ArrayCopy[y]);
            }
            if(checksort(ArrayCopy, n))
                puts("ok");
            else
                puts("no 2");
            free(ArrayCopy);
            //printf("LIBERTà 2\n");
            execTime = (double) (t2-t1) / CLOCKS_PER_SEC;
            timeQuick += execTime;

            ArrayCopy = copyArray(testArray,n);
            //printf("copia 3\n");
            t1 = clock();
            HeapSort(ArrayCopy, n);
            t2 = clock();
             if(n == 20){
                puts("Heap");
                for(int y=0; y<20; y++)
                    printf("%d\n", ArrayCopy[y]);
            }
            if(checksort(ArrayCopy, n))
                puts("ok");
            else
                puts("no 3");
            free(ArrayCopy);
            //printf("LIBERTà 3\n");
            execTime = (double)(t2-t1) / CLOCKS_PER_SEC;
            timeHeap += execTime;
        }
        printf("%lf,%lf,%lf\n", (timeBubble), (timeQuick), (timeHeap));
        fprintf(f,"%lf,%lf,%lf\n", (timeBubble), (timeQuick), (timeHeap));
        //free(testArray);
    }
    fclose(f);
    return 1;

}
