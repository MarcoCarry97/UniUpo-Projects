#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

typedef int DATA;  //struct necessarie per ottenere una lista

struct linked
{
	DATA d;
	struct linked *next;
};

typedef struct linked ELEMENT;
typedef ELEMENT *LINK;

LINK newnode(void)//crea un nuovo nodo in una lista
{ 
	return (ELEMENT *)malloc(sizeof(ELEMENT));
}

LINK crealista(int vet[],int num) //crea una lista utilizzando un vettore come input
{
	LINK head=NULL,p,last=NULL;
	for(int i=0;i<num;i++)
	{
		p=newnode();
		p->d=vet[i];
		p->next=NULL;
		if(head==NULL)
			head=p;
		else
			last->next=p;
		last=p;
	}
	return head;
}

int sommaric(LINK lis)
{
	if(lis->next==NULL)
		return lis->d;
	return lis->d + sommaric(lis->next);
}

int diffric(LINK lis, int *ris)
{
	if(lis!=NULL)
	{
		if(*ris==0)
			*ris=(lis->d);
		else
			*ris-=(lis->d);
		diffric(lis->next,ris);
	}
}

int prodric(LINK lis)
{
	if(lis->next==NULL)
		return lis->d;
	return lis->d * prodric(lis->next);
}

/*int quotoric(LINK lis)
{
	if(lis->next==NULL)
		return lis->d;
	return lis->d / quotoric(lis->next);
}*/

int main(int argc,char *argv[])
{
	int vet[argc-1];
	for(int i=1;i<=argc-1;i++)
		vet[i-1]=atoi(argv[i]);
	LINK lis=crealista(vet,argc-1);
	/*LINK p=lis;
	while(p!=NULL)
	{
		
		printf("%d\n",p->d);
		p=p->next;
	}*/
	int somma=sommaric(lis);
	int diff;
	diffric(lis, &diff);
	int prod=prodric(lis);
	//int quoto=quotoric(lis);
	printf("somma=%d\n",somma);
	printf("differenza=%d\n",diff);
	printf("prodotto=%d\n",prod);
//	printf("quoto=%d\n",quoto);
	return 0;
}
