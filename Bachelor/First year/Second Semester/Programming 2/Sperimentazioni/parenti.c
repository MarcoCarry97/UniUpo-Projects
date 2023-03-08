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

void getdata(DATA *d)
{
	scanf("%s",d->nome);
	scanf("%s",d->cogn);
	scanf("%d",&d->eta);
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

void addtesta(LINK *lis,LINK p)
{
	p->next=(*lis);
	(*lis)=p;
}

void addcoda(LINK *lis,LINK p)
{
	LINK q=(*lis);
	while(q!=NULL) q=q->next;
	q->next=p;
}

void stampadato(DATA d)
{
	printf("%s %s %d\n",d.nome,d.cogn,d.eta);
}

void stampalis(LINK lis)
{
	while(lis!=NULL)
	{
		stampadato(lis->d);
		lis=lis->next;
	}
}

void annoda(LINK *q, LINK p)
{
	p->next=(*q)->next;
	(*q)->next=p;
}

LINK crealista()
{
	LINK head=NULL,q=NULL;
	int nota;
	printf("crei una lista?\n");
	scanf("%d",&nota);
	while(nota)
	{
		DATA nodo;
		printf("inserire paramentri separati da spazio\n");
		getdata(&nodo);
		LINK p=newnode(nodo);
		if(p->d.eta>=18)
		{
			bool trovato=false;
			if(head==NULL) 
			{
				head=p;
				trovato=true;
			}
			else if(head->d.eta>=18)
			{
				addtesta(&head,p);
				trovato=true;
			}
			else
			{
				q=head;
				trovato=false;
				while(q->next!=NULL && !trovato)
				{
					if(q->next->d.eta>=18)
					{
						annoda(&q,p);
						trovato=true;
					}
					q=q->next;
				}
			}
			if(q->next==NULL && !trovato) addtesta(&head,p);
		}
		else
		{
			bool trovato=false;
			if(head==NULL)
			{
				head=p;
				trovato=true;
			}
			else if(head->d.eta<18)
			{
				addtesta(&head,p);
				trovato=true;
			}
			else
			{
				q=head;
				bool trovato=false;
				while(q->next!=NULL && !trovato)
				{
					if(q->next->d.eta<18)
					{
						annoda(&q,p);
						trovato=true;
					}
					q=q->next;
				}
			}
			if(q->next==NULL && !trovato) addtesta(&head,p);
		}
		printf("continuare?\n");
		scanf("%d",&nota);
	}
	return head;
}

void togliadd(LINK *head,LINK *tail,LINK *lis)
{
	if((*head)==NULL) (*head)=(*lis)->next;
	else (*tail)->next=(*lis)->next;
	(*tail)=(*lis)->next;
	(*lis)->next=(*lis)->next->next;
	(*tail)->next=NULL;
}

LINK parenti(LINK *lis, DATA d)
{
	LINK head=NULL, tail=NULL, q=(*lis);
	if((*lis)!=NULL)
		while(q->next!=NULL)
		{	
			if(!strcmp((*lis)->d.cogn,d.cogn))
			{
				if(head==NULL) head=(*lis);
				else tail->next=(*lis);
				tail=(*lis);
				(*lis)=(*lis)->next;
				tail->next=NULL;
			}
			if(!strcmp(q->next->d.cogn,d.cogn)) togliadd(&head,&tail,&q);
			q=q->next;
		}
	if(head!=NULL)
	{
		LINK p=newnode(d);
		addtesta(&head,p);
	}
	else printf("non ci non parenti\n");
	return head;
}

int main()
{
	LINK lis=crealista();
	printf("LISTA PRIMA\n");
	stampalis(lis);
	DATA person;
	printf("inserire dati di una persona per controllo parenti\n");
	getdata(&person);
	LINK par=parenti(&lis,person);
	printf("LISTA DOPO\n");
	stampalis(lis);
	printf("PARENTI\n");
	stampalis(par);
	return 0;
}
