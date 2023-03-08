#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define SIZE 10000

int *randomArray(int n);
void swap(int *a, int *b);
bool checksort(int a[], int n);
int partition(int a[], int i,int f);
void quickSort(int a[], int i, int f);

int main()
{
	int *a=randomArray(SIZE);
	quickSort(a,0,SIZE);
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

int partition(int a[], int i, int f)
{
	int x=a[i], inf=i+1,sup=f;
	while(inf<sup)
	{
		while(inf<=f && a[inf]<=x) inf++; 
		while( sup>=i && a[sup]>x) sup--; 
		if(inf<sup) swap(&a[inf++], &a[sup--]);
	}
	swap(&a[i], &a[sup]);
	return sup;
}

void quickSort(int a[], int i, int f)
{
	if(i<f)
	{
		int m=partition(a,i,f);
		quickSort(a,i,m-1);
		quickSort(a,m+1,f);
	}
}
