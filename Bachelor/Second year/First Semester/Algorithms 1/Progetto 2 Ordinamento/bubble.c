#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define SIZE 100

int *randomArray(int n);
void swap(int *a, int *b);
bool checksort(int a[], int n);
void bubbleSort(int a[], int n);

int main()
{
	int *a=randomArray(SIZE);
	bubbleSort(a,SIZE);
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

void bubbleSort(int a[], int n)
{
	for(int i=0;i<n;i++)
		for(int j=1;j<n-i;j++)
			if(a[j-1]>a[j])
				swap(&a[j],&a[j-1]);
}

