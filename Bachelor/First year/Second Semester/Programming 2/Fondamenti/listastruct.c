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

LINK crealista()
{
	LINK head=NULL, tail=NULL, p;
	int scegli;
	printf("vuoi creare una lista? digitare 1 per il Si e 0 per il No\n");
	scanf("%d",&scegli);
	while(scegli==1)
	{
		p=newnode();
		p->next=NULL;
		printf("inserire nome\n");
		scanf("%d",&p->d.nome);
		printf("inserire cognome\n");
		scanf("%d",&p->d.cogn);
		printf("inserire eta''\n");
		scanf("%d",&p->d.eta);
		if(head==NULL) head=p;
		else tail->next=p;
		tail=p;
		printf("vuoi aggiungere altri elementi? digitare 1 per il Si e 0 per il No\n");
		scanf("%d",&scegli);	
	}	
	return head;
}

void stampa(LINK lis)
{
	while(lis!=NULL)
	{
		printf("%s ",lis->d.nome);
		printf("%s ",lis->d.cogn);
		printf("%d\n",lis->d.eta);
		lis=lis->next;
	}
}

int main()
{
	LINK lis=crealista();
	stampa(lis);
	return 0;
}

