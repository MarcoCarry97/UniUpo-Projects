#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

typedef struct DATA
{
	char nome[15];
	char cogn[10];
	int eta;
}DATA;

typedef struct linked
{
	DATA d;
	struct linked *next;
}ELEMENT;
typedef ELEMENT *LINK;

LINK newnode(void)
{
	return (ELEMENT *)malloc(sizeof(ELEMENT));
}

LINK crealista(char nome[])
{
	LINK head=NULL, tail=NULL, p;
	int scegli;
	FILE *f=fopen(nome,"r");
	if(f==NULL)
	{
		printf("file non trovato\n");
		return NULL;
	}
	char *riga,s[100];
	do
	{
		p=newnode();
		p->next=NULL;
		fscanf(f,"%s %s %d",p->d.nome,p->d.cogn,&p->d.eta);
		if(head==NULL) head=p;
		else tail->next=p;
		tail=p;	
		riga=fgets(s,100,f);
		if(riga==NULL)break;
	}
	while(riga!=NULL);	
	return head;
}

void stampa(LINK lis,int num)
{
	int pos=1;
	while(lis!=NULL && pos<=num)
	{
		printf("%s ",lis->d.nome);
		printf("%s ",lis->d.cogn);
		printf("%d\n",lis->d.eta);
		lis=lis->next;
		pos++;
	}
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("inserire un solo valore\n");
		return 1;
	}
	LINK lis=crealista(argv[1]);
	if(lis==NULL) return 1;
	int num;
	printf("inserire numero per la stampa\n");
	scanf("%d",&num);
	stampa(lis,num);
	return 0;
}

