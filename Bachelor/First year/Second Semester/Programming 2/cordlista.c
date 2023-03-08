#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct cord
{
	int x;
	int y;
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
	p->d.x=d.x;
	p->d.y=d.y;
	p->next=NULL;
	return p;
}

void getscan(DATA *d)
{
	scanf("%d %d",&d->x,&d->y);
}

void addtesta(LINK *lis, DATA d)
{
	LINK p=newnode(d);
	p->next=(*lis);
	(*lis)=p;
}

LINK crealista(int num)
{
	LINK head=NULL;
	for(;num>=0;num--)
	{
		DATA d;
		printf("inserire coordinata\n");
		getscan(&d);
		addtesta(&head,d);
	}
	return head;
}

int contacord(LINK lis,DATA d)
{
	int conta=0;
	while(lis!=NULL)
	{
		if(lis->d.x==d.x && lis->d.y==d.y) conta++;
		lis=lis->next;
	}
	return conta;
}

LINK primoquad(LINK lis)
{
	LINK head=NULL;
	while(lis!=NULL)
	{
		if(lis->d.x>0 && lis->d.y>0) addtesta(&head,lis->d);
		lis=lis->next;
	}
	return head;
}

void scrivifile(char nome[],LINK lis)
{
	FILE *f=fopen(nome,"w");
	for(;lis!=NULL;lis=lis->next)
		fprintf(f,"%d %d\n",lis->d.x,lis->d.y);
	fclose(f);
}

int main()
{
	int num;
	printf("inserire numero per creazione lista coordinate\n");
	scanf("%d",&num);
	LINK lis=crealista(num);
	DATA d;
	printf("inserire coordinata per contatore\n");
	getscan(&d);
	printf("X=%d Y=%d Occorrenze: %d\n",d.x,d.y,contacord(lis,d));
	LINK primoq=primoquad(lis);
	char nome[20];
	printf("inserire nome del file\n");
	scanf("%s",nome);
	scrivifile(nome,primoq);
	return 0;
}
