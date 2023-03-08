#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct person
{
	char nome[20];
	char cognome[20];
	int eta;
}DATA;
typedef struct linked
{
	DATA d;
	struct linked *next;
}ELEMENT;
typedef ELEMENT *LINK;

void getscan(DATA *d)
{
	scanf("%s %s %d",d->nome,d->cognome,&d->eta);
}

void copia(LINK *p,DATA d)
{
	strcpy((*p)->d.nome,d.nome);
	strcpy((*p)->d.cognome,d.cognome);
	(*p)->d.eta=d.eta;
}

LINK newnode(DATA d)
{
	LINK p=(ELEMENT *)malloc(sizeof(ELEMENT));
	copia(&p,d);
	p->next=NULL;
	return p;
}

LINK crealista()
{
	int nota;
	LINK p=NULL;
	printf("inserire elemento?\n");
	scanf("%d",&nota);
	if(nota)
	{
		DATA d;
		printf("inserire parametri\n");
		getscan(&d);
		p=newnode(d);
		p->next=crealista();
	}
	return p;
}

void stampadato(DATA d)
{
	printf("%s %s %d\n",d.nome,d.cognome,d.eta);
}

void stampalis(LINK lis)
{
	if(lis!=NULL)
	{
		stampadato(lis->d);
		stampalis(lis->next);
	}
}

LINK ricercapos(LINK lis, int num,int pos)
{
	if(lis!=NULL)
	{
		if(pos==num) 
			return lis;
		else 
			return ricercapos(lis->next,num,pos+1);
	}
	else return NULL;
}

LINK ricercacogn(LINK lis, char cogn[])
{
	if(lis!=NULL)
	{
		if(!strcmp(lis->d.cognome,cogn)) return lis;
		else return ricercacogn(lis->next,cogn);
	}
	else return NULL;
}

bool parenti(LINK *lis,DATA d,bool trovato)
{
	if((*lis)==NULL || trovato) return trovato;
	else
	{
		if(!strcmp((*lis)->d.cognome,d.cognome))
		{
			LINK p=newnode(d);
			p->next=(*lis)->next;
			(*lis)->next=p;
			return parenti(&((*lis)->next),d,true);
		}
		else return parenti(&((*lis)->next),d,trovato);
	}
}

int main()
{
	LINK lis=crealista();
	stampalis(lis);
	LINK nodo;
	int nota;
	printf("scegliere ricerca 1=posizione 0=cognome\n");
	scanf("%d",&nota);
	if(nota)
	{
		int pos;
		printf("Inserire posizione\n");
		scanf("%d",&pos);
		nodo=ricercapos(lis,pos,1);
	}
	else
	{
		char cognome[20];
		printf("Inserire cognome\n");
		scanf("%s",cognome);
		nodo=ricercacogn(lis,cognome);
	}
	if(nodo==NULL) printf("ricerca fallita\n");
	else stampadato(nodo->d);
	DATA d;
	printf("inserire persona\n");
	getscan(&d);
	if(parenti(&lis,d,false)) stampalis(lis);
	else printf("non ci sono parenti\n");
	return 0;
}


