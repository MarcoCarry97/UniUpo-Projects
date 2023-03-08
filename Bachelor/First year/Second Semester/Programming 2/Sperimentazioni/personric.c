#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

typedef struct person
{
	char nome[10];
	char cogn[15];
	int eta;
}person;

void riempi(person vet[],int num)
{
	if(num-1>=0)
	{
		printf("inserire nome,cognome ed eta' separati da uno spazio\n");
		scanf("%s %s %d",vet[num-1].nome,vet[num-1].cogn,&vet[num-1].eta);
		riempi(vet,num-1);
	}
}

void stampa(person vet[], int num)
{
	printf("%s %s %d\n",vet[num].nome,vet[num].cogn,vet[num].eta);
}

void stampatutti(person vet[], int num)
{
	if(num-1>=0)
	{
		stampa(vet,num-1);
		stampatutti(vet,num-1);
	}
}

void transfer(person emit[], int pos1,person dest[],int pos2)
{
	strcpy(dest[(pos2)].nome,emit[(pos1)].nome);
	strcpy(dest[(pos2)].cogn,emit[(pos1)].cogn);
	dest[(pos2)].eta=emit[(pos1)].eta;
}

void dividi(person vet[], int num,person over[],int *mag,person under[], int *min)
{
	if(num-1>=0)
	{
		if(vet[num].eta>=18) transfer(vet,num,over,(*mag)++);
		else transfer(vet,num,under,(*min)++);
		dividi(vet,num-1,over,mag,under,min);
	}
	else
	{
		over=(person *)realloc(over,(*mag)*sizeof(person));
		under=(person *)realloc(under,(*min)*sizeof(person));
	}
}

int main()
{
	int num;
	printf("inserire grandezza vettore\n");
	scanf("%d",&num);
	person *vet=(person *)malloc(num*sizeof(person));
	riempi(vet,num);
	stampatutti(vet,num);
	person *magg=(person *)malloc(num*sizeof(person));
	person *minn=(person *)malloc(num*sizeof(person));
	int cmag=0,cmin=0;
	dividi(vet,num,magg,&cmag,minn,&cmin);
	printf("%d %d\n",cmag,cmin);
	printf("MAGGIONENNI\n");
	stampatutti(magg,cmag);
	printf("MINORENNI\n");
	stampatutti(minn,cmin);
	free(vet);
	free(magg);
	free(minn);
	return 0;
}
