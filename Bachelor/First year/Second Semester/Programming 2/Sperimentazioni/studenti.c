#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct studente
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
	int fine;
	fscanf(f,"%s",d->cognome);
	fscanf(f,"%s",d->nome);
	fscanf(f,"%d",&d->mat);
	fscanf(f,"%s",d->esame);
	fscanf(f,"%d",&d->crediti);
	fine=fscanf(f,"%d",&d->voto);
	return fine;
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

LINK crealista()
{
	LINK head=NULL, tail=NULL;
	FILE *f=fopen("input-esame.txt","r");
	DATA d;
	int fine=getdata(&d,f);
	while(fine!=EOF)
	{
		LINK p=newnode(d);
		if(head==NULL) head=p;
		else tail->next=p;
		tail=p;
		fine=getdata(&d,f);
	}
	fclose(f);
	return head;
}

int sommacrediti(LINK lis, int mat)
{
	if(lis!=NULL)
	{
		if(lis->d.mat==mat) return lis->d.crediti + sommacrediti(lis->next,mat);
		else return sommacrediti(lis->next,mat);
	}
	return 0;
}

void stampadato(DATA d)
{
	printf("%s ",d.cognome);
	printf("%s ",d.nome);
	printf("%d ",d.mat);
	printf("%s ",d.esame);
	printf("%d ",d.crediti);
	printf("%d\n",d.voto);
}

void stampalis(LINK lis)
{
	if(lis!=NULL)
	{
		stampadato(lis->d);
		stampalis(lis->next);
	}
}

LINK solocogn(LINK *lis,char cogn[])
{
	LINK head=NULL,tail=NULL,p;
	if((*lis)!=NULL)
	{
		LINK q=(*lis);
		while(q->next!=NULL)
		{
			if(!strcmp(q->d.cognome,cogn))
			{
				p=q;
				q=q->next;
				p->next=NULL;
				if(head==NULL) head=p;
				else tail->next=p;
				tail=p;
			}
			else if(!strcmp(q->next->d.cognome,cogn))
			{
				p=q->next;
				q->next=q->next->next;
				p->next=NULL;
				if(head==NULL) head=p;
				else tail->next=p;
				tail=p;
			}
			else q=q->next;
		}
	}
	return head;
}

int main()
{
	LINK lis=crealista();
	stampalis(lis);
	int mat;
	printf("inserire matricola\n");
	scanf("%d",&mat);
	int crediti=sommacrediti(lis,mat);
	printf("crediti di %d: %d\n",mat,crediti);
	char cogn[20];
	printf("inserire cognome\n");
	scanf("%s", cogn);
	LINK stud=solocogn(&lis,cogn);
	stampalis(stud);
	printf("RIMANENTE\n");
	stampalis(lis);
	return 0;
}
