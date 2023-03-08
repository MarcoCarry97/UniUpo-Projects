#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define dim 100

int *sequenza(char stri[], int *k)
{
	int num=10,conta=0;
	int *vet=(int *)malloc(num*sizeof(int));
	int len=strlen(stri); // salvo la lunghezza della stringa in una variabile
	for(int i=0;i+2<len;i++)
	{
		if(conta==num) //se il vettore ha raggiunto la sua dimensione massima, la incremento e rialloco.
		{
			num+=num;
			vet=(int *)realloc(vet,num*sizeof(int));
		}
		if(stri[i]==0x41) //Confronto 3 cifre alla volta a partire da i,0x41 è il codice ASCII esadecimale della lettera A.
			if(stri[i+1]==0x41)
				if(stri[i+2]==0x41)
					vet[conta++]=i+1; //salvo la posizione della prima A e passo alla cella successiva
	}
	*k=conta; //restituisco, tramite il puntatore, il valore di conta
	vet=(int *)realloc(vet,(*k)*sizeof(int)); //rialloco il vettore per avere esattamente conta posizioni.
	return vet;
}

int main()
{
	char stri[dim];
	printf("inserire stringa\n");
	scanf("%s",stri);
	int conta=0;
	int *pos=sequenza(stri,&conta);
	printf("DIM: %d\n",conta);
	for(int i=conta-1;i>=0;i--) //stampa il vettore al contrario
		printf("%d\n",pos[i]);
	free(pos); //libero la porzione di spazio allocata in precedenza
	return 0;
}
