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

void addtesta(LINK *head,int num)
{
	LINK p=newnode();
	p->d=num;
	p->next=(*head);
	(*head)=p;
}

LINK invlis(LINK lis)
{
	LINK head=NULL,tail=NULL,p;
	while(lis!=NULL)
	{
		p=newnode();
		p->next=NULL;
		if(head==NULL)
			head=p;
		else
			tail->next=p;
		tail=p;
		addtesta(&head,lis->d);
		lis=lis->next;
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
	LINK lis1=crealista();
	LINK lis2=invlis(lis1);
	stampalis(lis2);
	return 0;
}
