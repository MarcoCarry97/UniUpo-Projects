#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<time.h>

#define RUN 1000000

int *randomArray(int n);
int copyArray(int a[], int n);
void swap(int *a, int *b);
bool checksort(int a[], int n);
void bubbleSort(int a[], int n);
int partition(int a[], int i,int f);
void quickSort(int a[], int i, int f);
void fixHeap(int a[],int i, int n);
void heapify(int a[], int n);
void heapSort(int a[], int n);

int main()
{
	int num=10;
	int *dim=(int *)malloc(sizeof(int));
	assert(dim!=NULL);
	dim[0]=10;
	for(int i=1;i<num;i++) dim[i]=dim[i-1]*2;
	FILE *f=fopen("ris.cfw","w");
	assert(f!=NULL);
	for(int i=0;i<num;i++)
	{
		int size=dim[i];
		double timeB=0,timeQ=0,timeH=0;
		int *a;
		double execTime;
		clock_t ti,tf;
		for(int j=0;j<RUN;j++)
		{
			a=randomArray(size);
			//BUBBLESORT
			int *b=copyArray(a,size);
			ti=clock();
			bubbleSort(b,size);
			tf=clock();
			if(checksort(b,size)) printf("ok\n");
			else printf("no\n");
			free(b);
			execTime=(double)(tf-ti)/CLOCKS_PER_SEC;
			timeB+=execTime;
			//QUICKSORT
			b=copyArray(a,size);
			ti=clock();
			quickSort(b,0,size);
			tf=clock();
			if(checksort(b,size)) printf("ok\n");
			else printf("no\n");
			free(b);
			execTime=(double)(tf-ti)/CLOCKS_PER_SEC;
			timeQ+=execTime;
			//HEAPSORT
			b=copyArray(a,size);
			ti=clock();
			heapSort(b,size);
			tf=clock();
			if(checksort(b,size)) printf("ok\n");
			else printf("no\n");
			free(b);
			execTime=(double)(tf-ti)/CLOCKS_PER_SEC;
			timeH+=execTime;
		}
		fprintf(f,"%lf,%lf,%lf\n",timeB,timeQ,timeH);
		free(a);
	}
	fclose(f);
	return 1;
}

int *randomArray(int n)
{
	int *a=(int *)malloc(n*sizeof(int));
	assert(a!=NULL);
	for(int i=0;i<n;i++) a[i]=(int)rand() % n;
	return a;
}

int copyArray(int a[], int n)
{
	int *b=(int *)malloc(n*sizeof(int));
	assert(b!=NULL);
	for(int i=0;i<n;i++) b[i]=a[i];
	return *b;
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

int partition(int a[], int i, int f)
{
	int x=a[i], inf=i,sup=f+1;
	while(inf<sup)
	{
		do inf++; while(inf<=f && a[inf]<=x);
		do sup--; while(a[sup]>x);
		if(inf<sup) swap(&a[inf], &a[sup]);
	}
	swap(&a[i], &a[sup]);
	return sup;
}

void bubbleSort(int a[], int n)
{
	for(int i=0;i<n;i++)
		for(int j=1;j<n-i;j++)
			if(a[j-1]>a[j])
				swap(&a[j],&a[j-1]);
}

void quickSort(int a[], int i, int f)
{
	int m=partition(a,i,f);
	quickSort(a,i,m-1);
	quickSort(a,m+1,f);
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
