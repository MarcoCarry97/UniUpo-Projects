#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct fisica
{
	char codice[1];
	float valore;
	int num;
} fisica;

typedef struct lista
{
	fisica d;
	struct lista *prossimo;
} lis;
typedef lis *lista;

void crealiste(lista *a,lista *b,lista *c);
void mediavar(lista lis);
float sommalis(lista lis, int *k);

lista newnode()
{
	return (lis *)malloc(sizeof(lis));
}

void stampa(lista lis)
{
	while(lis!=NULL)
	{
		printf("%s %f %d\n",lis->d.codice,lis->d.valore,lis->d.num);
		lis=lis->prossimo;
	}
}

int main()
{
	lista lisa=NULL,lisb=NULL,lisc=NULL;
	crealiste(&lisa,&lisb,&lisc);
	//printf("LISTE CREATE\n");
	//stampa(lisa);
	//printf("lsita a stampata, incomincio mediavar\n");
	mediavar(lisa);
	mediavar(lisb);
	mediavar(lisc);
	return 0;
}

void crealiste(lista *a,lista *b,lista *c)
{
	lista taila=NULL,tailb=NULL,tailc=NULL;
	int nota;
	printf("vuoi creare una lista?\n");
	scanf("%d",&nota);
	while(nota)
	{
		lista p = newnode();
		printf("inserisci dati\n");
		scanf("%s",p->d.codice);
		scanf("%f",&p->d.valore);
		scanf("%d",&p->d.num);
		p->prossimo=NULL;
		if(strcmp(p->d.codice,"a")==0)
		{
			if((*a)==NULL) (*a)=p;
			else taila->prossimo=p;
			taila=p;
		}	
		else if(strcmp(p->d.codice,"b")==0)
		{
			if((*b)==NULL) (*b)=p;
			else tailb->prossimo=p;
			tailb=p;
		}
		else
		{
			if((*c)==NULL) (*c)=p;
			else tailc->prossimo=p;
			tailc=p;
		}
		printf("vuoi continuare?\n");
		scanf("%d",&nota);		
	}
}

float sommalis(lista lis, int *k)
{
	float somma=0;
	int conta=0;
	while(lis!=NULL)
	{
	//	printf("sommo\n");
		somma+=lis->d.valore;
		conta++;
	//	printf("incremento\n");
		lis=lis->prossimo;
	}
	(*k)=conta;
	return somma;
}

void mediavar(lista lis)
{
	int k;
	//printf("calcolo la somma\n");
	float somma = sommalis(lis,&k);
	//printf("calcolo la media\n");
	float media = somma / k;
	printf("MEDIA: %f\n",media);
	somma=0;
	while(lis!=NULL)
	{
		//printf("continua\n");
		somma += pow(lis->d.valore-media,2);
		lis=lis->prossimo;
	}
	printf("VARIANZA: %f\n",somma/k);
}

