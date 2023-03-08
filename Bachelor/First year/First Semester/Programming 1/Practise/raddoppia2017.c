/*Scrivere una procedura C 
int *raddoppia(int a[], int n, int *d)

che dato un array a[] contenente n interi, 
alloca e restituisce un array di interi contenente tutti i valori di a[] diversi da 0 seguiti dal loro doppio. 
Ad esempio (con notazione Python) se

  a = [17, 3, 4, 0, -1]

l'array di interi restituito deve essere

  [17, 34, 3, 6, 4, 8, -1, -2]

L'indirizzo dell'array di output deve essere restituito attraverso l'istruzione return mentre la lunghezza dell'array deve essere memorizzata in d. 
Scrivere anche la procedura main() che invoca *raddoppia e stampa il relativo output. */

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<math.h>

int *raddoppia(int a[], int num, int *dim)
{
int *rad=(int *) malloc(num*sizeof(int));
if(rad==NULL)
{
	printf("Memoria insufficiente\n");
	exit(1);
}
int conta=0;
for(int i=0;i<num;i++)
if(a[i]!=0)
{
	rad[conta++]=a[i];
	rad[conta++]=a[i]*2;
}
rad=(int *) realloc(rad, conta*sizeof(int));
*dim=conta;
return rad;
}

int main(int argc, char *argv[]) 
{
	if(argc<=2)
	{
		printf("Inserire piu' di un valore\n");
		return 1;
	}
	
int vet[argc];
int siz;
for(int i=0;i<argc;i++)
{
	vet[i]=atoi(argv[i]);
}
	
int *a=raddoppia(vet,argc,&siz);
for(int i=0;i<siz;i++)
	printf("%d\n",a[i]);
free(a);
return 0;
}










