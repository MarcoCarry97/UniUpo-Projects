#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct esame
{
	int codice;
	int voto;
	int mat;
	int lode;
}DATA;
typedef struct linked
{
	DATA d;
	struct linked *next;
}ELEMENT;
typedef ELEMENT *LINK;

void getscan(DATA *d)
{
	scanf("%d %d %d",&d->codice,&d->voto,&d->mat);
	while(d->voto<18 || d->voto>30)
	{
		printf("scegliere un'altro voto");
		scanf("%d",&d->voto);
	}
	if(d->voto==30) d->lode=1;
	else d->lode==0;
}

LINK newnode(DATA d)
{
	LINK p=(ELEMENT *)malloc(sizeof(ELEMENT));
	p->d.codice=d.codice;
	p->d.voto=d.voto;
	p->d.mat=d.mat;
	p->d.lode=d.lode;
	p->next=NULL;
	return p;
}

void addtesta(LINK *lis,LINK p)
{
	p->next=(*lis);
	(*lis)=p;
}

void insert(LINK *head,LINK p)
{
	if((*head)==NULL) (*head)=p;
	else if((*head)->d.codice>p->d.codice) addtesta(head,p);
	else insert(&((*head)->next),p);
}

LINK crealista(int num)
{
	LINK head=NULL;
	while(num>0)
	{
		DATA d;
		printf("inserire esame\n");
		getscan(&d);
		LINK p=newnode(d);
		insert(&head,p);
		num--;
	}
	return head;
}

LINK solouno(LINK lis,int code)
{
	LINK p=NULL;
	if(lis!=NULL)
	{
		if(lis->d.codice==code)
		{
			p=newnode(lis->d);
			p->next=solouno(lis->next,code);
		}
		else return solouno(lis->next,code);
	}
	return p;
}

void massimovoto(LINK lis,int code,int voto)
{
	if(lis!=NULL)
	{
		if(lis->next!=NULL)
		{
			if(code==lis->next->d.codice)
			{
				if(voto<lis->next->d.voto)
					massimovoto(lis->next,lis->next->d.codice,lis->next->d.voto);
				else massimovoto(lis->next,lis->next->d.codice,voto);
			}
			else
			{
				printf("%d: %d\n",code,voto);
				massimovoto(lis->next,lis->next->d.codice,lis->next->d.voto);
			}
		}
		else printf("%d: %d",code,voto);
	}
}

void stampalis(LINK lis)
{
	while(lis!=NULL)
	{
		printf("%d %d %d %d\n",lis->d.codice,lis->d.voto,lis->d.mat,lis->d.lode);
		lis=lis->next;
	}
}

int main()
{
	int n;
	printf("inserire numero esami\n");
	scanf("%d",&n);
	LINK lis=crealista(n);
	stampalis(lis);
	int code;
	printf("inserire codice corso\n");
	scanf("%d",&code);
	stampalis(solouno(lis,code));
	massimovoto(lis,lis->d.codice,lis->d.voto);
	return 0;
}
