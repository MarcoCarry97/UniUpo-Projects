#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define RUN 10000

int *creaArrayRandon(int n);
int *copyArray(int a[],int n);
void swap(int *a,int *b);
void bubbleSort(int a[],int n);
int partition(int a[],int begin, int end);
void quickSort(int a[],int begin,int end);
void fixHeap(int a[],int i,int size);
void heapify(int a[],int size);
void heapSort(int a[],int size);

int main()
{
	srand(time(NULL));
	int numeroRun= 10;
	int dimensioni[]={5,10,25,50,100,200,500,1000,2000};
	for (i=0;i<9;i++)
	{
		int N=9;
		double timeBubble=0, timeQuick=0, timeHeap=0;
		for (k=1;k<numeroRun,k++)
		{
			int testArray[]=creaArrayRandom(N);
			int arrayDaOrdinare[]=copiaArray(testArray, n);
			clock_t T1=clock();
			bubbleSort(arrayDaOrdinare, N);
			clock_t T2=clock();
			timeBubble=timeBubble+((double)(T2-T1)/CLOCKS_PER_SEC;
			free(arrayDaOrdinare);
			int arrayDaOrdinare[]=copiaArray(testArray, n);
			int T1=currentTime();
			quicksort(arrayDaOrdinare, N);
			int T2=currentTime();
			timeQuick=timeQuick+(T2-T1);
			free(arrayDaOrdinare);
			int arrayDaOrdinare[]=copiaArray(testArray, n);
			int T1=currentTime();
			heapsort(arrayDaOrdinare, N);
			int T2=currentTime();
			timeHeap=timeHeap+(T2-T1);
			free(arrayDaOrdinare);
			free(testArray);
		}
	printf("%d, %d, %d\n",timeBubble,timeQuick,timeHeap);	
	}
	return 0;
}

int *creaArrayRandom(int n)
{
	int *b=(int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++) 
		b[i]=(int)rand();
	return b;
}

int *copyArray(int a[],int n)
{
	int *b=(int *)malloc(n*sizeof(int));
	memcpy(b,a,n*sizof(int));
	return b;
}

void swap(int *a, int *b)
{
	int tmp=(*a);
	(*a)=(*b);
	(*b)=tmp;
}

void bubbleSort(int a[],int n)
{
	int lastSwap=n-1, swapped=1,tmp=0;
	while(swapped>0)
	{
		swapped=0;
		for(int i=0;i<lastSwap-1;i++)
			if(a[i]>a[i+1])
			{
				swap(&a[i],&a[i+1]);
				tmp=i;
				swapped=1;
			}
		}
		lastSwap=tmp;
	}
}

int partition(int a[],int begin, int end)
{
	int pivot=a[begin],inf=begin+1,suè=end;
	while(inf<=sup)
	{
		while(a[sup]>pivot) sup--;
		while(a[inf]<=pivot && inf<=sup) inf++;
		if(inf<sup)
		{
			swap(&a[inf],&a[sup]);
			inf++;
			sup--;
		}
	}
	swap(&a[begin],&a[sup]);
	return sup;
}

void quickSort(int a[],int begin, int end)
{
	if(begin<end)
	{
		int q=partition(a,begin,end);
		quickSort(a,begin,q-1);
		quickSort(a,q+1,end);
	}
}

void fixHeap(int a[],int i, int size)
{
	int left=2*i+1, right=2*i+2, large;
	if(left<size && a[left]>a[i]) large=left;
	else large=i;
	if(right<size && a[right]>a[large]) large=right;
	if(large!=i)
	{
		swap(&a[i],&a[large]);
		fixHeap(a,large,size);
	}
}

void heapify(int a[],int size)
{
	for(int i=size/2;i>=0;i--)
		fixHeap(a,i,size);
}

void heapSort(int a[], int size)
{
	int hSize=size;
	heapify(a,size);
	for(int i=size-1;i>=1;i++)
	{
		swap(&a[0],&a[i]);
		hSize--;
		fixHeap(a,0,hSize);
	}
}
