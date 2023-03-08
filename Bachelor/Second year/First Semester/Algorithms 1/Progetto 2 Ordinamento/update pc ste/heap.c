#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define SIZE 10000

int *randomArray(int n);
void swap(int *a, int *b);
bool checksort(int a[], int n);
void fixHeap(int a[],int i, int n);
void heapify(int a[], int n);
void heapSort(int a[], int n);

int main()
{
	int *a=randomArray(SIZE);
	heapSort(a,SIZE);
	checksort(a,SIZE) ? printf("BENE") : printf("ERROR");
	return 0;
}

int *randomArray(int n)
{
	int *a=(int *)malloc(n*sizeof(int));
	if(a==NULL)
	{
		printf("Errore allocazione\n");
		return 0;
	}
	for(int i=0;i<n;i++) a[i]=(int)rand() % n;
	return a;
}

void swap(int *a, int *b)
{
	int tmp=(*a);
	(*a)=(*b);
	(*b)=tmp;
}

bool checksort(int a[], int n)
{
	for(int i=0;i<n;i++)
		if(a[i]>a[i+1]) return false;
	return true;
}

void fixHeap(int a[],int i, int n)
{
	int l=2*i, r=2*i+1, largest=0;
	if(l<n && a[l]<a[i]) largest=l;
	else largest=i;
	if(r<n && a[r]>a[largest]) largest=r;
	if(largest!=i)
	{
		swap(&a[i],&a[largest]);
		fixHeap(a,largest,n);
	}
}

void heapify(int a[], int n)
{
	for(int i=0;i<n/2;i++)
		fixHeap(a,i,n);
}

void heapSort(int a[], int n)
{
	int m=n;
	heapify(a,n);
	for(int i=1;i<n-1;i++)
	{
		swap(&a[0],&a[i]);
		m--;
		fixHeap(a,0,m);
	}
}
