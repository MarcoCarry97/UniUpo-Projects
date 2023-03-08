#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

#define	MAX	3 
#define	N 50 
#define	MAX_AMICI 50

typedef struct indirizzo
{
	char via[N];
	int numero;
	int cap;
	char loc[N];
}indirizzo;

typedef	struct	pers
{	
	char nome[N];
	char cognome[N];
	int	eta;
    indirizzo i;
	int	codice_pers;
	int	num_amici;
	int	amici[MAX_AMICI];
}DATA;

typedef struct linked
{
	DATA d;
	struct linked *next;
}ELEMENT;
typedef ELEMENT *LINK;

LINK newnode()
{
	return (ELEMENT *)malloc(sizeof(ELEMENT));
}

void carica(DATA *x)
{
	scanf("%s %s %d %s %d %d %s %d %d",x->nome,x->cognome,&x->eta,x->i.via,&x->i.numero,&x->i.cap,x->i.loc,&x->codice_pers,&x->num_amici);
	for(int i=0;i<x->num_amici;i++)
		scanf("%d",&x->amici[i]);
}

int getdata(DATA *x,FILE *f)
{
	fscanf(f,"%s %s %d %s %d %d %s %d %d",x->nome,x->cognome,&x->eta,x->i.via,&x->i.numero,&x->i.cap,x->i.loc,&x->codice_pers,&x->num_amici);
	int end=0;
	for(int i=0;i<x->num_amici;i++)
		end=fscanf(f,"%d",&x->amici[i]);
	return end;
}

void copia(LINK *p, DATA d)
{
	strcpy((*p)->d.nome,d.nome);
	strcpy((*p)->d.cognome,d.cognome);
	(*p)->d.eta=d.eta;
	strcpy((*p)->d.i.via,d.i.via);
	(*p)->d.i.numero=d.i.numero;
	(*p)->d.i.cap=d.i.cap;
	strcpy((*p)->d.i.loc,d.i.loc);
	(*p)->d.codice_pers=d.codice_pers;
	(*p)->d.num_amici=d.num_amici;
	for(int i=0;i<d.num_amici;i++)
		(*p)->d.amici[i]=d.amici[i];
}

LINK crealista(char nome[])
{
	LINK head=NULL, tail=NULL,p;
	FILE *f=fopen(nome,"r");
	if(f==NULL)
	{
		printf("file non trovato\n");
		return NULL;
	}
	DATA x;
	int max=getdata(&x,f);
	while(max!=EOF)
	{
		p=newnode();
		copia(&p,x);
		p->next=NULL;
		if(head==NULL)head=p;
		else tail->next=p;
		tail=p;
		max=getdata(&x,f);
	}
	fclose(f);
	return head;
}

void stampadato(DATA d)
{
	printf("NOME: %s\n",d.nome);
	printf("COGNOME: %s\n",d.cognome);
	printf("ETA': %d\n",d.eta);
	printf("VIA: %s\n",d.i.via);
	printf("NUMERO: %d\n",d.i.numero);
	printf("CAP: %d\n",d.i.cap);
	printf("LOCALITA': %s\n",d.i.loc);
	printf("CODICE PERSONA: %d\n",d.codice_pers);
	printf("NUMERO AMICI: %d\n",d.num_amici);
	for(int i=0;i<d.num_amici;i++)
		printf("AMICO %d: %d\n",i+1,d.amici[i]);
	printf("\n");
}

void stampalis(LINK lis)
{
	while(lis!=NULL)
	{
		stampadato(lis->d);
		lis=lis->next;
	}
}

bool ctrlcodice(int vet[], int dim,int code)
{
	bool trovato=false;
	for(int i=0;i<dim && !trovato;i++)
		if(vet[i]==code)
			trovato=true;
	return trovato;
}

LINK friends(LINK lis, DATA d)
{
	LINK head=NULL,tail=NULL,p;
	while(lis!=NULL)
	{
		if(ctrlcodice(d.amici,d.num_amici,lis->d.codice_pers))
		{
			p=newnode();
			copia(&p,lis->d);
			p->next=NULL;
			if(head==NULL) head=p;
			else tail->next=p;
			tail=p;
		}
		lis=lis->next;
	}
	return head;
}

void write(DATA d,FILE *f)
{
	fprintf(f,"%d ",d.codice_pers);
	fprintf(f,"%s ",d.nome);
	fprintf(f,"%s ",d.cognome);
	fprintf(f,"%d ",d.eta);
	fprintf(f,"%s ",d.i.via);
	fprintf(f,"%d ",d.i.numero);
	fprintf(f,"%d ",d.i.cap);
	fprintf(f,"%s ",d.i.loc);
	fprintf(f,"%d ",d.num_amici);
	for(int i=0;i<d.num_amici;i++)
		fprintf(f,"%d ",d.amici[i]);
	fprintf(f,"\n");
}

void scrivifile(LINK lis, char nome[])
{
	FILE *f=fopen(nome,"w");
	if(f==NULL)
	{
		printf("impossibile creare file\n");
		return;
	}
	while(lis!=NULL)
	{
		write(lis->d,f);
		lis=lis->next;
	}
	fclose(f);
}

LINK trova(LINK lis, char nome[],char cogn[])
{
	LINK p=NULL;
	bool trovato=false;
	while(lis!=NULL && !trovato)
	{
		if(strcmp(lis->d.nome,nome) && strcmp(lis->d.cognome,cogn))
		{
			p=lis;
			trovato=true;
		}
		else lis=lis->next;
	}
	return p;
}

LINK ricerca(LINK lis,LINK nodo)
{
	LINK head=NULL,tail=NULL,p;
	while(lis!=NULL)
	{
		if(!strcmp(lis->d.i.via,nodo->d.i.via) && lis->d.i.cap==nodo->d.i.cap && !strcmp(lis->d.i.loc,nodo->d.i.loc))
		{
			p=newnode();
			copia(&p,lis->d);
			p->next=NULL;
			if(head==NULL) head=p;
			else tail->next=p;
			tail=p;
		}
		lis=lis->next;
	}
	return head;
}

void toglidup(LINK *q)
{
	LINK lis=(*q),p=(*q);
	if(lis!=NULL)
	{
		while(lis->next!=NULL && p!=NULL)
		{
			if(strcmp(p->d.nome,lis->next->d.nome) || strcmp(p->d.nome,lis->next->d.nome) || lis->next->d.codice_pers!=p->d.codice_pers)
			{
				LINK q=lis->next;
				lis->next=lis->next->next;
				free(q);
			}
			else lis=lis->next;
			if(lis->next==NULL && p!=NULL)
			{
				lis=(*q);
				p=p->next;
			}
		}
	}	
}

void vicini(LINK lis,char nome[], char cogn[])
{
	//printf("trovo il nodo interessato\n");
	LINK p=trova(lis,nome,cogn);
	//printf("cerco i vicini\n");
	LINK q=ricerca(lis,p);
	//printf("tolgo i duplicati\n");
	toglidup(&q);
	stampalis(q);
}

LINK maxmin(LINK lis, int max, int min)
{
	LINK head=NULL,tail=NULL,p;
	while(lis!=NULL)
	{
		if(lis->d.eta<=max &&lis->d.eta>=min)
		{
			p=newnode();
			copia(&p,lis->d);
			p->next=NULL;
			if(head==NULL) head=p;
			else tail->next=p;
			tail=p;
		}
		lis=lis->next;
	}
	return head;
}

LINK cercaloc(LINK lis, char loca[], float *media)
{
	int somma=0, conta=0;
	LINK head=NULL, tail=NULL,p;
	while(lis!=NULL)
	{
		if(!strcmp(lis->d.i.loc,loca))
		{
			p=newnode();
			copia(&p,lis->d);
			p->next=NULL;
			somma+=p->d.eta;
			conta++;
			if(head==NULL) head=p;
			else tail->next=p;
			tail=p;
		}
		lis=lis->next;
	}
	(*media)=somma/conta;
	return head;
}

int main()
{
	LINK lis=crealista("personeEstese.txt");
	stampalis(lis);
	DATA pers;
	printf("Inserire persona per lista amici\n");
	carica(&pers);
	LINK amici=friends(lis,pers);
	scrivifile(amici,"amici.txt");
	char nome[N],cogn[N];
	printf("inserire nome e cognome per controllo vicini\n");
	scanf("%s %s",nome,cogn);
	vicini(lis,nome,cogn);
	int max=0, min=0;
	while(max<=min)
	{
		printf("inserire un valore massimo e minimo per controllo eta'\n");
		scanf("%d %d",&max,&min);
		if(max<=min) printf("Non prendermi in giro...\n");
	}
	LINK etalis=maxmin(lis,max,min);
	stampalis(etalis);
	float media=0;
	char localita[N];
	printf("inserire nome localita' per controllo abitanti\n");
	scanf("%s",localita);
	LINK abitanti=cercaloc(lis,localita,&media);
	stampalis(abitanti);
	printf("eta' media degli abitanti di %s: %.1f anni\n",localita,media);
	return 0;
}
