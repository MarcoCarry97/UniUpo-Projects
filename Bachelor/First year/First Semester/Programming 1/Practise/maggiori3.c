/* Scrivere una procedura C:  bool *maggiori3(int a[], int n)

che prende in input un array a[] di n interi e restituisce un array di n 
booleani b[] tale che b[i]==true se e solo se i>=3 e a[i] e' maggiore dei tre elementi che lo precedono: a[i-1], a[i-2], a[i-3] (vedere esempi piu' sotto).
Scrivere poi una funzione main() che legge degli interi dalla linea di comando e, dopo averli convertiti con atoi(), 
li scrive in un array x[] opportunamente allocato. Il main() deve poi passare questo array a maggiori3 e utilizzare il risultato fornito 
da maggiori3 per stampare un elenco dei valori e delle posizioni degli elementi di x[] che risultano maggiori dei tre elementi che li precedono. 
Esempi: la linea di comando

  maggiori3 11 13 -4 25 36 8 9 10   deve produrre l'output

  3: 25
  4: 36
il comando
 maggiori3 23 45 71 100 101 4 200
l'output
 3: 100
  4: 101
  6: 200
il comando
 maggiori3 23 45 71 100 100 4 200
l'output
 3: 100
  6: 200
(l'elemento di posto 4 e' stato escluso peche' non e' maggiore stretto dell'elemento di posto 3). */


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<math.h>

bool *maggiori3(int a[], int n)
{
	bool *magg=(bool *) malloc (n*sizeof(bool));
	if(magg==NULL)
	{
		printf("Memoria insufficiente\n");
		exit(1);
	}
for(int i=0;i<n;i++)
{
	if(a[i]>=3 && a[i]>a[i-2] && a[i]>a[i-3] && a[i]>a[i-4])
	{
		magg[i]=true;
	}
	else
		magg[i]=false;
	
}
return magg;
}

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("Inserire piu' di un valore\n");
		return 1;
	}
	
int vet[argc];
for(int i=0;i<argc;i++)
{
	vet[i]=atoi(argv[i]);
}
bool *a=maggiori3(vet, argc);
for(int i=0;i<argc;i++)
	if(a[i])
	printf("%d\n",vet[i]);
free(a);
return 0;
}








