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

bool dup(LINK lis, DATA d)
{
	bool dupl=false;
	while(lis!=NULL && !dupl)
	{
		if(!strcmp(lis->d.targa,d.targa))
			if(!strcmp(lis->d.telaio,d.telaio))
				if(!strcmp(lis->d.proprietario,d.proprietario)) dupl=true;
		lis=lis->next;
	}
	return dupl;
}

int getdata(DATA *d,FILE *f)
{
	return fscanf(f,"%s %s %s",d->targa,d->telaio,d->proprietario);
}

void addtesta(LINK *lis,LINK p)
{
	p->next=(*lis);
	(*lis)=p;
}

void insertcre(LINK *head,DATA d)
{
	LINK p;
	p=newnode(d);
	if((*head)==NULL) (*head)=p;
	else if(strcmp(p->d.targa,(*head)->d.targa)>0) addtesta(head,p);
	else insertcre(&((*head)->next),d);
}

void insertdec(LINK *head,DATA d)
{
	LINK p;
	p=newnode(d);
	if((*head)==NULL) (*head)=p;
	else if(strcmp(p->d.targa,(*head)->d.targa)<0) addtesta(head,p);
	else insertcre(&((*head)->next),d);
}

LINK crealista(char nome[])
{
	LINK head=NULL;
	DATA d;
	FILE *f=fopen(nome,"r");
	int fine=getdata(&d,f);
	while(fine!=EOF)
	{
		if(!dup(head,d)) insertcre(&head,d);
		fine=getdata(&d,f);
	}
	fclose(f);
	return head;
}

LINK neolista(char nome[],LINK lis)
{
	LINK head=NULL;
	DATA d;
	FILE *f=fopen(nome,"r");
	int fine=getdata(&d,f);
	while(fine!=EOF)
	{
		if(!dup(head,d) && !dup(lis,d)) insertcre(&head,d);
		fine=getdata(&d,f);
	}
	fclose(f);
	return head;
}

LINK listaord(LINK l1,LINK l2)
{
	LINK head=NULL;
	while(l1!=NULL && l2!=NULL)
	{
		if(strcmp(l1->d.targa,l2->d.targa)>0)
		{
			insertdec(&head,l1->d);
			l1=l1->next;
		}
		else
		{
			insertdec(&head,l2->d);
			l2=l2->next;
		}
	}
	while(l1!=NULL)
	{
		insertdec(&head,l1->d);
		l1=l1->next;
	}
	while(l2!=NULL)
	{
		insertdec(&head,l2->d);
		l2=l2->next;
	}
	return head;
}

void stampadato(DATA d)
{
	printf("%s %s %s\n",d.targa,d.telaio,d.proprietario);
}

void stampalis(LINK lis)
{
	if(lis!=NULL)
	{
		stampadato(lis->d);
		stampalis(lis->next);
	}
}

int main()
{
	LINK l1=crealista("file1.txt");
	LINK l2=neolista("file2.txt",l1);
	LINK l3=listaord(l1,l2);
	stampalis(l1);
	printf("\n");
	stampalis(l2);
	printf("\n");
	stampalis(l3);
	return 0;
}
