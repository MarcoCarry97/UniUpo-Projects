//CREARE DUE LISTE ORDINATE (CRESCENTE) SENZA DUPLICATI E CREARE UNA TERZA LISTA ORDINATA (DECRESCENTE) TOGLIENDO I NODI DA QUELLE DI ORIGINE
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct car
{
	char targa[20];
	char telaio[20];
	char proprietario[20];
}DATA;
typedef struct linked
{
	DATA d;
	struct linked *next;
}ELEMENT;
typedef ELEMENT *LINK;

LINK newnode(DATA d)
{
	LINK p=(ELEMENT *)malloc(sizeof(ELEMENT));
	strcpy(p->d.targa,d.targa);
	strcpy(p->d.telaio,d.telaio);
	strcpy(p->d.proprietario,d.proprietario);
	p->next=NULL;
	return p;
}

bool dup(LINK lis,DATA d)
{
	bool dupl=false;
	while(lis!=NULL && !dupl)
	{
		if(!strcmp(lis->d.targa,d.targa) && !strcmp(lis->d.telaio,d.telaio) && !strcmp(lis->d.proprietario,d.proprietario)) dupl=true;
		else lis=lis->next;
	}
	return dupl;
}

void getscan(DATA *d)
{
	scanf("%s %s %s",d->targa,d->telaio,d->proprietario);
}

void addtesta(LINK *lis,LINK p)
{
	p->next=(*lis);
	(*lis)=p;
}

void addnodo(LINK *lis, LINK p)
{
	p->next=(*lis)->next;
	(*lis)->next=p;
}

LINK crealista()
{
	LINK head=NULL;
	DATA x;
	int nota;
	printf("crei una lista?\n");
	scanf("%d",&nota);
	while(nota)
	{
		printf("inserire dati separati da spazio\n");
		getscan(&x);
		if(dup(head,x)==false)
		{
			LINK p=newnode(x);
			if(head==NULL) head=p;
			else if(strcmp(p->d.targa,head->d.targa)<0) addtesta(&head,p);
			else
			{
				LINK q=head;
				bool trovato=false;
				while(q->next!=NULL && !trovato)
				{
					if(strcmp(p->d.targa,q->next->d.targa)<0)
					{
						addnodo(&q,p);
						trovato=true;
					}
					q=q->next;
				}
				if(!trovato) addnodo(&q,p);
			}
		}
		else printf("il dato e' gia' presente nella lista\n");
		printf("continuare?\n");
		scanf("%d",&nota);
	}
	return head;
}

LINK neolista(LINK lis)
{
	LINK head=NULL;
	DATA x;
	int nota;
	printf("crei una lista?\n");
	scanf("%d",&nota);
	while(nota)
	{
		printf("inserire dati separati da spazio\n");
		getscan(&x);
		if(dup(head,x)==false && dup(lis,x)==false)
		{
			LINK p=newnode(x);
			if(head==NULL) head=p;
			else if(strcmp(p->d.targa,head->d.targa)<0) addtesta(&head,p);
			else
			{
				LINK q=head;
				bool trovato=false;
				while(q->next!=NULL && !trovato)
				{
					if(strcmp(p->d.targa,q->next->d.targa)<0)
					{
						addnodo(&q,p);
						trovato=true;
					}
					q=q->next;
				}
				if(!trovato) addnodo(&q,p);
			}
		}
		else printf("il dato e' gia' presente in una delle due liste\n");
		printf("continuare?\n");
		scanf("%d",&nota);
	}
	return head;
}

LINK listaord(LINK *l1, LINK *l2)
{
	LINK head=NULL,p;
	while((*l1)!=NULL && (*l2)!=NULL)
	{
		if(strcmp((*l1)->d.targa,(*l2)->d.targa)<0)
		{
			p=(*l1);
			(*l1)=(*l1)->next;
		}
		else
		{
			p=(*l2);
			(*l2)=(*l2)->next;
		}
		p->next=NULL;
		if(head==NULL) head=p;
		else if(strcmp(p->d.targa,head->d.targa)>0) addtesta(&head,p);
		else
		{
			LINK q=head;
			bool trovato=false;
			while(q->next!=NULL && !trovato)
			{
				if(strcmp(p->d.targa,head->next->d.targa)>0)
				{
					addnodo(&q,p);
					trovato=true;
				}
				else q=q->next;
			}
			if(trovato==false) addnodo(&q,p);
		}
	}
		while((*l1)!=NULL)
	{
		p=(*l1);
		(*l1)=(*l1)->next;
		p->next=NULL;
		if(head==NULL) head=p;
		else if(strcmp(p->d.targa,head->d.targa)>0) addtesta(&head,p);
		else
		{
			LINK q=head;
			bool trovato=false;
			while(q->next!=NULL && !trovato)
			{
				if(strcmp(p->d.targa,head->next->d.targa)>0)
				{
					addnodo(&q,p);
					trovato=true;
				}
				else q=q->next;
			}
			if(trovato==false) addnodo(&q,p);
		}
	}
		while((*l2)!=NULL)
	{
		p=(*l2);
		(*l2)=(*l2)->next;
		p->next=NULL;
		if(head==NULL) head=p;
		else if(strcmp(p->d.targa,head->d.targa)>0) addtesta(&head,p);
		else
		{
			LINK q=head;
			bool trovato=false;
			while(q->next!=NULL && !trovato)
			{
				if(strcmp(p->d.targa,head->next->d.targa)>0)
				{
					addnodo(&q,p);
					trovato=true;
				}
				else q=q->next;
			}
			if(trovato==false) addnodo(&q,p);
		}
	}
	return head;
}

void stampadato(DATA d)
{
	printf("%s %s %s\n",d.targa,d.telaio,d.proprietario);
}

void stampalis(LINK lis)
{
	while(lis!=NULL)
	{
		stampadato(lis->d);
		lis=lis->next;
	}
}

int main()
{
	LINK l1=crealista();
	stampalis(l1);
	LINK l2=neolista(l1);
	stampalis(l2);
	printf("\n");
	LINK l3=listaord(&l1,&l2);
	stampalis(l3);
	return 0;
}
