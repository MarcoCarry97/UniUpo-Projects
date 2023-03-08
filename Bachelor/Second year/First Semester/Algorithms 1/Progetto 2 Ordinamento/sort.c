#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define RUN 10000

int *creaArrayRandom(int n);
int *copiaArray(int a[],int n);
void swap(int *a,int *b);
void bubbleSort(int a[],int n);
int partition(int a[],int begin, int end);
void quickSort(int a[],int begin,int end);
void fixHeap(int a[],int i,int size);
void heapify(int a[],int size);
void heapSort(int a[],int size);
bool checksort(int a[],int n);

int main()
{
	FILE *f=fopen("ris.csv","w");
	if(f==NULL)
	{
		printf("Impossibile creare file");
		return 0;
	}
	srand(time(NULL));
	int dimensioni=5;
	for (int i=0;i<10;i++)
	{
		int N=dimensioni;
		double timeBubble=0, timeQuick=0, timeHeap=0,execTime=0;
		for (int k=1;k<RUN;k++)
		{
			int *testArray=creaArrayRandom(N);
			printf("Bubble? ");
			int *arrayDaOrdinare=copiaArray(testArray, N);
			clock_t T1=clock();
			bubbleSort(arrayDaOrdinare, N);
			clock_t T2=clock();
			execTime=(double)(T2-T1)/CLOCKS_PER_SEC;
			timeBubble+=execTime;
			checksort(arrayDaOrdinare,N) ? printf("Yes\n") : printf("No\n");
			free(arrayDaOrdinare);
			printf("Quick?  ");
			arrayDaOrdinare=copiaArray(testArray, N);
			T1=clock();
			quickSort(arrayDaOrdinare, 0, N);
			T2=clock();
			execTime=(double)(T2-T1)/CLOCKS_PER_SEC;
			timeQuick+=execTime;
			checksort(arrayDaOrdinare,N) ? printf("Yes\n") : printf("No\n");
			free(arrayDaOrdinare);
			printf("Heap?   ");
			arrayDaOrdinare=copiaArray(testArray, N);
			T1=clock();
			heapSort(arrayDaOrdinare, N);
			T2=clock();
			execTime=(double)(T2-T1)/CLOCKS_PER_SEC;
			timeHeap+=execTime;
			checksort(arrayDaOrdinare,N) ? printf("Yes\n") : printf("No\n");
			free(arrayDaOrdinare);
			free(testArray);
		}
		fprintf(f,"%lf,%lf,%lf\n",timeBubble,timeQuick,timeHeap);	
		dimensioni*=2;
	}
	fclose(f);
	return 0;
}

int *creaArrayRandom(int n)
{
	int *b=(int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++) 
		b[i]=(int)rand();
	return b;
}

int *copiaArray(int a[],int n)
{
	int *b=(int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)b[i]=a[i];
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
	/*int lastSwap=n-1, swapped=1,tmp=0;
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
		lastSwap=tmp;
	}*/
	for(int i=0;i<n;i++)
		for(int j=0;j<n-i-1;j++)
			if(a[j]>a[j+1])
				swap(&a[j],&a[j+1]);
}

int partition(int a[],int begin, int end)
{
	int pivot=a[begin],inf=begin+1,sup=end;
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
	//printf("Fix Heap \n");
	int left=2*i+1, right=2*i+2, large=0;
	if(left<size && a[left]>a[i]) large=left;
	else large=i;
	//printf("Fix Heap \n");
	if(right<size && a[right]>a[large]) large=right;
	//printf("Fix Heap \n");
	if(large!=i)
	{
		swap(&a[i],&a[large]);
		fixHeap(a,large,size);
	}
	//printf("Fix Heap \n");
}

void heapify(int a[],int size)
{
	//printf("Heapify ");
	for(int i=(size-1)/2;i>=0;i--)
		fixHeap(a,i,size);
}

void heapSort(int a[], int size)
{
	int hSize=size;
	heapify(a,size);
	for(int i=size-1;i>=1;i--)
	{
		swap(&a[0],&a[i]);
		hSize--;
		fixHeap(a,0,hSize);
	}
}

bool checksort(int a[],int n)
{
	for(int i=0;i<n-1;i++)
		if(a[i]>a[i+1]) return false;
	return true;
}
