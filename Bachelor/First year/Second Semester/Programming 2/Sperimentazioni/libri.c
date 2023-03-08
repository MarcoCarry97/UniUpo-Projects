#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct book
{
	char nome[20];
	char autore[20];
	int prezzo;
	int disp;
}DATA;
typedef struct linked
{
	DATA d;
	struct linked *next;
}ELEMENT;
typedef ELEMENT *LINK;

void getscan(DATA *d)
{
	scanf("%s %s %d %d",d->nome,d->autore,&d->prezzo,&d->disp);
}

void copia(LINK *p,DATA d)
{
	strcpy((*p)->d.nome,d.nome);
	strcpy((*p)->d.autore,d.autore);
	(*p)->d.prezzo=d.prezzo;
	(*p)->d.disp=d.disp;
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
	LINK p=NULL;
	int nota;
	printf("inserire elemento?\n");
	scanf("%d",&nota);
	if(nota)
	{
		DATA d;
		printf("inserire libro\n");
		getscan(&d);
		p=newnode(d);
		p->next=crealista();
	}
	return p;
}

void stampadato(DATA d)
{
	printf("%s %s %d€ %d\n",d.nome,d.autore,d.prezzo,d.disp);
}

void stampalis(LINK lis)
{
	if(lis!=NULL)
	{
		stampadato(lis->d);
		stampalis(lis->next);
	}
}

void stampabook(LINK lis, int disp)
{
	if(lis!=NULL)
	{
		if(lis->d.disp>=disp)
		{
			stampadato(lis->d);	
			stampabook(lis->next,disp);
		}
		else stampabook(lis->next,disp);
	}
}

void stampabookinv(LINK lis, int disp)
{
	if(lis!=NULL)
	{
		if(lis->d.disp>=disp)
		{
			stampabookinv(lis->next,disp);
			stampadato(lis->d);	
		}
		else stampabookinv(lis->next,disp);
	}
}

LINK entrambiIT(LINK l1,LINK l2)
{
	LINK head=NULL,tail=NULL;
	while(l1!=NULL)
	{
		LINK q=l2;
		bool trovato=false;
		while(q!=NULL && !trovato)
		{
			if(!strcmp(l1->d.nome,q->d.nome))
			{
				LINK p=newnode(l1->d);
				if(head==NULL) head=p;
				else tail->next=p;
				tail=p;
				trovato=true;
			}
			else q=q->next;
		}
		l1=l1->next;
	}
	return head;
}

LINK entrambiRIC(LINK l1,LINK l2,LINK q)
{
	LINK p=NULL;
	if(l1!=NULL)
	{
		if(l2!=NULL)
		{
			if(!strcmp(l1->d.nome,l2->d.nome))
			{
				p=newnode(l1->d);
				p->next=entrambiRIC(l1->next,q,q);
			}
			else return entrambiRIC(l1,l2->next,q);
		}
		else return entrambiRIC(l1->next,q,q);
	}
	return p;
}

int main()
{
	LINK lis=crealista();
	int disp;
	printf("inserire numero per controllo disponibilità\n");
	scanf("%d",&disp);
	stampabook(lis,disp);
	printf("AL CONTRARIO\n");
	stampabookinv(lis,disp);
	LINK lis2=crealista();
	printf("ITERAZIONE\n");
	stampalis(entrambiIT(lis,lis2));
	printf("RICORSIONE\n");
	stampalis(entrambiRIC(lis,lis2,lis2));
	return 0;
}
