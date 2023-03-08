#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

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

void getdata(DATA *d)
{
	scanf("%d",&d->x);
	scanf("%d",&d->y);
}

LINK newnode(DATA d)
{
	LINK p=(ELEMENT *)malloc(sizeof(ELEMENT));
	p->d.x=d.x;
	p->d.y=d.y;
	p->next=NULL;
	return p;
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

LINK crealista()
{
	LINK head=NULL,tail=NULL;
	int nota;
	printf("vuoi creare una lista?\n");
	scanf("%d",&nota);
	while(nota)
	{
		DATA cord;
		printf("inserire coordinate separate da spazio\n");
		getdata(&cord);
		LINK p=newnode(cord);
		if(head==NULL)head=p;
		else tail->next=p;
		tail=p;
		printf("continuare?\n");
		scanf("%d",&nota);
	}
	return head;
}

void noprimoquad(LINK *lis)
{
	LINK q=(*lis);
	if(q!=NULL)
		while(q->next!=NULL)
		{
			if(q->d.x>=0 && q->d.y>=0)
			{ 
				toglitesta(&q);
				(*lis)=q;
			}
			else if(q->next->d.x>=0 && q->next->d.y>=0) toglinodo(&q);
			else q=q->next;
		}
}

LINK terzoquad(LINK l1,LINK l2)
{
	LINK head=NULL, tail=NULL,p;
	while(l1!=NULL)
	{
		if(l1->d.x<0 && l1->d.y<0)
		{
			p=newnode(l1->d);
			if(head==NULL) head=p;
			else tail->next=p;
			tail=p;
		}
		l1=l1->next;
	}
	while(l2!=NULL)
	{
		if(l2->d.x<0 && l2->d.y<0)
		{
			p=newnode(l2->d);
			if(head==NULL) head=p;
			else tail->next=p;
			tail=p;
		}
		l2=l2->next;
	}
	return head;	
}

LINK insieme(LINK l1,LINK l2,int n,int m)
{
	LINK head=NULL,tail=NULL,p;
	int pos=1;
	while(l1!=NULL && l2!=NULL)
	{
		if(pos<=n) p=newnode(l1->d);
		else if(pos<=m)
		{
			if(l1->d.y>l2->d.y) p=newnode(l1->d);
			else p=newnode(l2->d);
		}
		else p=newnode(l2->d);
		if(head==NULL) head=p;
		else tail->next=p;
		tail=p;
		l1=l1->next;
		l2=l2->next;
		pos++;
	}
	while(l1!=NULL)
	{
		if(pos<=m)
		{
			p=newnode(l1->d);
			if(head==NULL) head=p;
			else tail->next=p;
			tail=p;
		}
		l1=l1->next;
		pos++;
	}
	while(l2!=NULL)
	{
		if(pos>n) 
		{
			p=newnode(l2->d);
			if(head==NULL) head=p;
			else tail->next=p;
			tail=p;
		}
		l2=l2->next;
		pos++;
	}
	return head;
}

void stampadato(DATA d)
{
	printf("X:%d ",d.x);
	printf("Y:%d\n",d.y);
}

void stampalis(LINK lis)
{
	while(lis!=NULL)
	{
		stampadato(lis->d);
		lis=lis->next;
	}
}

void listcpy(LINK *dest, LINK emit)
{
	(*dest)=NULL;
	LINK tail=NULL;
	while(emit!=NULL)
	{
		LINK p=newnode(emit->d);
		if((*dest)==NULL) (*dest)=p;
		else tail->next=p;
		tail=p;
		emit=emit->next;
	}
}

void delist(LINK *lis)
{
	while((*lis)!=NULL)
		toglitesta(lis);
}

int main()
{
	LINK l1=crealista();
	LINK l2;
	listcpy(&l2,l1);
	noprimoquad(&l1); 
	printf("SENZA PRIMO QUADRANTE\n");
	stampalis(l1);
	LINK treq=terzoquad(l1,l2);
	printf("TERZO QUADRANTE\n");
	stampalis(treq);
	int n,m;
	printf("inserire valori n ed m\n");
	scanf("%d %d",&n,&m);
	LINK ins=insieme(l1,l2,n,m);
	printf("INSIEME NM\n");
	stampalis(ins);
	delist(&l1);
	delist(&l2);
	return 0;
}
