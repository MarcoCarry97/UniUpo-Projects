#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define RUN 100000

int *randomArray(int n);
int *copyArray(int a[], int n);
void swap(int *a, int *b);
bool checksort(int a[], int n);
void bubbleSort(int a[], int n);
int partition (int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void fixHeap(int a[],int i, int n);
void heapify(int a[], int n);
void heapSort(int a[], int n);

int main()
{
	int dim=1, bc=0,qc=0,hc=0;
	FILE *f=fopen("ris.txt","w");
	if(f==NULL)
	{
		printf("Errore creazione file\n");
		return 0;
	}
	for(int i=0;i<10;i++)
	{
		double timeB=0, timeQ=0, timeH=0, execTime;
		clock_t ti, tf;
		for(int j=0;j<RUN;j++)
		{
			int *a=randomArray(dim);
			//BUBBLESORT
			//printf("BubbleSort\n");
			int *b=copyArray(a,dim);
			ti=clock();
			bubbleSort(b,dim);
			tf=clock();
			checksort(b,dim) ? bc++ : printf(" NB ");
			execTime=(double)(tf-ti)/CLOCKS_PER_SEC;
			timeB+=execTime;
			free(b);
			//QUICKSORT
			//printf("QuickSort\n");
			b=copyArray(a,dim);
			ti=clock();
			quickSort(b,0,dim);
			tf=clock();
			checksort(b,dim) ? qc++ : printf(" NQ ");
			execTime=(double)(tf-ti)/CLOCKS_PER_SEC;
			timeQ+=execTime;
			free(b);   
			//HEAPSORT
			//printf("HeapSort\n");
			b=copyArray(a,dim);
			ti=clock();
			heapSort(b,dim);
			tf=clock();
			checksort(b,dim) ? hc++ : printf(" NH \n");
			execTime=(double)(tf-ti)/CLOCKS_PER_SEC;
			timeH+=execTime;
			free(b);
			free(a);
		}
		dim*=2;
		fprintf(f,"%lf,%lf,%lf\n",timeB,timeQ,timeH);
	}
	fclose(f);
	printf("Success sort: %db %db %dh\n",bc,qc,hc);
	return 1;
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

int *copyArray(int a[], int n)
{
	int *b=(int *)malloc(n*sizeof(int));
	if(b==NULL)
	{
		printf("Errore allocazione\n");
		return 0;
	}
	for(int i=0;i<n;i++) b[i]=a[i];
	return b;
}

void swap(int *a, int *b){ //richiede due indirizzi di memoria in entrata che verranno memorizzati in 2 puntatori.
int temp; //la variabile d'appoggio che memorizza temporaneamente il valore di a.
temp = *a;
*a = *b;
*b = temp;

bool checksort(int a[], int n)
{
	for(int i=0;i<n;i++)
		if(a[i]>a[i+1]) return false;
	return true;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void bubbleSort(int a[], int n)
{
for(i = 0; i < n - 1; i++) //scansiona tutto l'array tranne l'ultima componente: n - 1 escluso. Quindi fino al penultimo elemento.
      for (j = n - 1; j > i; j--) //j settato all'ultima componente e decresce ad ogni iterazione. Esce dal ciclo solo se j <= i
                  if (a[j] < a[j-1])  //se la componente corrente è più piccola della precedente, li scambia.
                          scambia(&a[j],&a[j-1]);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
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
		printf("8==D");
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
