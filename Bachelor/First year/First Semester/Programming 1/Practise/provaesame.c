#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

typedef struct student
{
	char cognome[20];
	char nome[20];
	int mat;
	char esame[20];
	int crediti;
	int voto;
}DATA;
typedef struct linked
{
	DATA d;
	struct linked *next;
}ELEMENT;
typedef ELEMENT *LINK;

int getdata(DATA *d,FILE *f)
{
	fscanf(f,"%s",d->cognome);
	fscanf(f,"%s",d->nome);
	fscanf(f,"%d",&d->mat);
	fscanf(f,"%s",d->esame);
	fscanf(f,"%d",&d->crediti);
	int c=fscanf(f,"%d",&d->voto);
	return c;
}

void copia(LINK *p,DATA d)
{
	strcpy((*p)->d.cognome,d.cognome);
	strcpy((*p)->d.nome,d.nome);
	(*p)->d.mat=d.mat;
	strcpy((*p)->d.esame,d.esame);
	(*p)->d.crediti=d.crediti;
	(*p)->d.voto=d.voto;
}

LINK newnode(DATA d)
{
	LINK p=(ELEMENT *)malloc(sizeof(ELEMENT));
	copia(&p,d);
	p->next=NULL;
	return p;
}

LINK crealista(char nome[])
{
	LINK head=NULL,tail=NULL;
	FILE *f=fopen(nome,"r");
	if(f==NULL)
	{
		printf("File non trovato\n");
		exit(1);
	}
	DATA x;
	int c=getdata(&x,f);
	while(c!=EOF)
	{
		LINK p=newnode(x);
		if(head==NULL) head=p;
		else tail->next=p;
		tail=p;
		c=getdata(&x,f);
	}
	fclose(f);
	return head;
}

void stampadato(DATA d)
{
	printf("%s %s %d %s %d %d\n",d.cognome,d.nome,d.mat,d.esame,d.crediti,d.voto);
}

void stampalis(LINK lis)
{
	if(lis!=NULL)
	{
		stampadato(lis->d);
		stampalis(lis->next);
	}
}

int sumcrediti(LINK lis, int matri)
{
	if(lis==NULL) return 0;
	else if(lis->d.mat==matri) return lis->d.crediti+sumcrediti(lis->next,matri);
	else return sumcrediti(lis->next,matri);
}

void toglitesta(LINK *lis)
{
	LINK p=(*lis);
	(*lis)=(*lis)->next;
	free(p);
}

void toglinodo(LINK *lis)
{
	LINK p=(*lis)->next;
	(*lis)->next=(*lis)->next->next;
	free(p);
}

LINK solocogn(LINK (*lis),char cogn[])
{
	LINK head=NULL,tail=NULL,q=(*lis),p;
	if(q!=NULL)
		while(q->next!=NULL)
		{
			if(!strcmp(q->d.cognome,cogn))
			{
				p=newnode(q->d);
				toglitesta(&q);
				(*lis)=q;
				if(head==NULL) head=p;
				else tail->next=p;
				tail=p;
			}
			else if(!strcmp(q->next->d.cognome,cogn))
			{
				p=newnode(q->next->d);
				toglinodo(&q);
				if(head==NULL) head=p;
				else tail->next=p;
				tail=p;
			}
			else q=q->next;
		}
	return head;
}

int main()
{
	LINK lis=crealista("input.txt");
	stampalis(lis);
	int matri;
	printf("inserire matricola per somma voti\n");
	scanf("%d",&matri);
	printf("crediti totali di %d: %d\n",matri,sumcrediti(lis, matri));
	char cogn[20];
	printf("inserire cognome per somma lista\n");
	scanf("%s",cogn);
	LINK liscogn=solocogn(&lis,cogn);
	stampalis(liscogn);
	printf("LIS\n");
	stampalis(lis);
	return 0;
}

