// Inserisco una stringa di lunghezza arbitraria,
// la quale verrà analizzata da una funzione che memorizzerà la posizione all'interno di un vettore e,
// attraverso un contatore, conterà la quantità di volte in cui troverà la sequenza "AAA".
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define dim 100 //dimensione massima della stringa

int *sequenza(char *,int *conta);
void stampavet(int vet[],int conta);

int main()
{
	char str[dim];
	printf("Inserisci sequenza formata da sole lettere: A, C, T, G\n");
	scanf("%s", str);
	int conta;
	int *vet=sequenza(str,&conta); //Dichiaro un puntatore ad intero che punta a un vettore.
	printf("Dimensione vettore: %d\n", conta);
	stampavet(vet,conta); //Stampo il vettore al contrario.
	free(vet); // libero la porzione di spazio allocata in precedenza.
	return 0; 	
}

int *sequenza(char stri[], int *conta) //restituisce un vettore allocato contenente le posizioni di AAA
{
	int N=10; //dimesione massima inziale del vettore
	int *vet=(int *)malloc(N*sizeof(int)); //alloco lo spazio per un vettore.
	int len=strlen(stri); //salvo la lunghezza del vettore in una variabile.
	for (int i=0;i+2<len;i++)	
	{
		char pos1[2],pos2[2],pos3[2];
		snprintf(pos1,2,"%c",stri[i]);	
		snprintf(pos2,2,"%c",stri[i+1]); //snprintf é una variante di printf che stampa all'interno di una stringa	
		snprintf(pos3,2,"%c",stri[i+2]);	//in questo caso si memorizza tre lettere alla volta
		if(strcmp(pos1,"A")==0)
			if(strcmp(pos2,"A")==0) // Se tutte e tre le lettere sono uguali ad A, salvo la posizione della prima lettera A.
				if(strcmp(pos3,"A")==0)
				{
					vet[(*conta)]=i+1;
					(*conta)++;
				}
		if((*conta)==N) //Se ho raggiunto la dimensione massima del vettore, la incremento e rialloco il vettore.
		{
			N=N*N;
			vet=(int *)realloc(vet,N*sizeof(int));
		}
	}
	vet=(int *)realloc(vet,(*conta)*sizeof(int)); //rialloco il vettore per portare esattamente a conta posizioni.
	return vet;
}

void stampavet(int vet[],int conta) //Stampa il vettore al contrario
{
	for(int i=conta-1;i>=0;i--)
	{
		printf("%d\n",vet[i]);
	}
}


