#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

typedef  int DATA; // struct che servono per avere una lista
 
struct linked_list
{       
DATA d;   
struct linked_list *next;  
}; 
 
typedef struct linked_list ELEMENT; 
typedef ELEMENT * LINK; 

LINK newnode(void) //crea un nuovo nodo in una lista;
{
	return (ELEMENT *)malloc(sizeof(ELEMENT));
}

LINK crealista() //crea una lista
{
    int x;
	LINK lis, p, last;      
	printf("nuovo numero da inserire in lista:\n");      
	scanf("%d", &x);      
	if(x<=0)      
		lis= NULL; // caso di lista vuota    
	else          
	{// inserzione del primo elemento in una lista           
		last=newnode();               
		lis = last;               
		last->d = x;               
		last->next = NULL;             
		printf("nuovo numero da inserire in lista:\n");               
		scanf("%d", &x);               
		while (x>0)                
		{                     
			p=newnode();                     
			p->d = x;                     
			p->next = NULL;                     
			last->next = p;                     
			last = p;      
			printf("nuovo numero da inserire in lista:\n");         
			scanf("%d", &x);               
		}         
	}      
	return(lis); 
} 

LINK sommaliste(LINK lis1, LINK lis2)
{
	int acc=0;
	LINK head=NULL,tail=NULL,p;
	while(lis1!=NULL && lis2!=NULL)
	{
		//printf("primo while\n");
		p=newnode();
		//printf("somma\n");
		acc+=lis1->d+lis2->d;
		p->d=acc;
		//printf("%d\n",p->d);
		//printf("prossimo\n");
		p->next=NULL;
		//printf("controllo\n");
		if(head==NULL)
			head=p;
		else
			tail->next=p;
		tail=p;
		//printf("nodo successivo\n");
		lis1=lis1->next;
		lis2=lis2->next;
	}
	while(lis1!=NULL)
	{
		//printf("secondo while\n");
		p=newnode();
		acc+=lis1->d;
		p->d=acc;
		//printf("%d\n",p->d);
		//printf("prossimo\n");
		p->next=NULL;
		if(head==NULL)
			head=p;
		else
			tail->next=p;
		tail=p;
		//printf("assegna\n");
		lis1=lis1->next;
	}
	while(lis2!=NULL)
	{
		//printf("terzo while\n");
		p=newnode();
		acc+=lis2->d;
		p->d=acc;
		//printf("%d\n",p->d);
		p->next=NULL;
		if(head==NULL)
			head=p;
		else
			tail->next=p;
		tail=p;
		
		lis2=lis2->next;
	}
	return head;
}

void stampalis(LINK lis)
{
	while(lis!=NULL)
	{
		printf("%d\n",lis->d);
		lis=lis->next;
	}
}

int main()
{
	LINK l1=crealista(),l2=crealista();
	LINK somma=sommaliste(l1,l2);
	stampalis(somma);
	return 0;
}
