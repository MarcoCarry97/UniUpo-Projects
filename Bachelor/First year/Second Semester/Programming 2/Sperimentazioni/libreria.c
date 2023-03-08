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
	printf("%s %s %d %d\n",d.nome,d.autore,d.prezzo,d.disp);
}

void stampalis(LINK lis)
{
	for(;lis!=NULL;lis=lis->next)
		stampadato(lis->d);
}

LINK libriaut(LINK lis, char autore[])
{
	LINK p=NULL;
	if(lis!=NULL)
	{
		if(!strcmp(lis->d.autore,autore))
		{
			p=newnode(lis->d);
			p->next=libriaut(lis->next,autore);
		}
		else return libriaut(lis->next,autore);
	}
	return p;
}

void delnodo(LINK *lis)
{
	LINK p=(*lis);
	(*lis)=(*lis)->next;
	free(p);
}

void acquisto(LINK *lis,DATA d)
{
	if((*lis)!=NULL)
	{
		if(!strcmp((*lis)->d.nome,d.nome))
		{
			(*lis)->d.disp-=d.disp;
			if((*lis)->d.disp<0)
			{
				printf("Mancano ancora %d libri",0-(*lis)->d.disp);
				delnodo(&(*lis));
			}
			else if((*lis)->d.disp==0) delnodo(&(*lis));
		}
	}
}

LINK dup(LINK p,LINK q)
{
	LINK n=NULL;
	if(p==NULL) return n;
	else if(!strcmp(p->d.nome,q->d.nome))
		if(strcmp(p->d.autore,q->d.autore))
			return n;
	return dup(p->next,q);
}

LINK unione(LINK l1,LINK l2)
{
	LINK p=NULL,q;
	if(l1!=NULL)
	{
		q=dup(p,l1);
		if(q==NULL)
		{
			q=newnode(l1->d);
			q->next=unione(l1->next,l2);
		}
		else
		{
			if(l1->d.prezzo>q->d.prezzo) q->d.prezzo=l1->d.prezzo;
			q->d.prezzo+=l1->d.prezzo;
		}
	}
	if(l2!=NULL)
	{
		q=dup(p,l2);
		if(q==NULL)
		{
			q=newnode(l2->d);
			q->next=unione(l1->next,l2);
		}
		else
		{
			if(l2->d.prezzo>q->d.prezzo) q->d.prezzo=l2->d.prezzo;
			q->d.prezzo+=l2->d.prezzo;
		}
	}
	return p;
}

int main()
{
	LINK l1=crealista();
	char aut[20];
	printf("inserire autore\n");
	scanf("%s",aut);
	LINK autore=libriaut(l1,aut);
	stampalis(autore);
	DATA d;
	printf("inserire libro\n");
	getscan(&d);
	acquisto(&l1,d);
	stampalis(l1);
	LINK l2=l1;
	LINK l3=unione(l1,l2);
	stampalis(l3);
	return 0;
}
