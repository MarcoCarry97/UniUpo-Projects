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

int sommapesata(LINK lis,int x)
{
	int somma=0,pos=1;
	while(lis!=NULL)
	{
		if(pos%x==0)
			somma+=pos*(lis->d);
		pos++;
		lis=lis->next;
	}
	return somma;
}

/*void stampalista(LINK lis)
{
	int pos=1;
	while(lis!=NULL)
	{
		printf("pos %d: %d\n",pos,lis->d);
		pos++;
		lis=lis->next;
	}
}*/

int main(int argc, char *argv[])
{
	int vet[argc-1];
	for(int i=1;i<=argc-1;i++)
		vet[i-1]=atoi(argv[i]);
	int x;
	printf("inserire valore x\n");
	scanf("%d",&x);
	LINK lis=crealista(vet,argc-1);
	///stampalista(lis);
	int somma=sommapesata(lis,x);
	printf("%d\n",somma);
	return 0;
}
