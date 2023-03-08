#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

typedef struct person
{
	char nome[12];
	char cogn[10];
	int eta;
}DATA;

typedef struct linked
{
	DATA d;
	struct linked *next;
}ELEMENT;
typedef ELEMENT *LINK;

int getdata(DATA *d,FILE *f)
{
	int max;
	fscanf(f,"%s",d->nome);
	fscanf(f,"%s",d->cogn);
	max=fscanf(f,"%d",&d->eta);
	return max;
}

LINK newnode(DATA d)
{
	LINK p=(ELEMENT *)malloc(sizeof(ELEMENT));
	strcpy(p->d.nome,d.nome);
	strcpy(p->d.cogn,d.cogn);
	p->d.eta=d.eta;
	p->next=NULL;
	return p;
}

LINK crealista(char nome[])
{
	LINK head=NULL,tail=NULL;
	FILE *f=fopen(nome,"r");
	if(f==NULL)
	{
		printf("file non trovato\n");
		exit(1);
	}
	DATA nodo;
	int max=getdata(&nodo,f);
	while(max!=EOF)
	{
		LINK p=newnode(nodo);
		if(head==NULL)head=p;
		else tail->next=p;
		tail=p;
		max=getdata(&nodo,f);
	}
	fclose(f);
	return head;
}

void stampadato(DATA d)
{
	printf("%s %s %d\n",d.nome,d.cogn,d.eta);
}

void stampalis(LINK lis, int num)
{
	int pos=1;
	while(lis!=NULL && pos<=num)
	{
		stampadato(lis->d);
		lis=lis->next;
		pos++;
	}
}

int main()
{
	LINK lis=crealista("persone.txt");
	int n;
	printf("inserire numero per stampa\n");
	scanf("%d",&n);
	stampalis(lis,n);
}
