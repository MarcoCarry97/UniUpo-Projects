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
typedef ELEMENT *LINK; 

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

int contalis(LINK lis, int num)
{
	int conta=0;
	while(lis!=NULL)
	{
		if(lis->d==num)
			conta++;
		lis=lis->next;
	}
	return conta;
}

int sommalis(LINK lis, int num)
{
	int somma=0,pos=1;
	while(lis!=NULL)
	{
		if(pos%num==0)
			somma+=lis->d;
		pos++;
		lis=lis->next;
	}
	return somma;
}

int main()
{
	LINK lis=crealista();
	int x;
	printf("inserire valore x\n");
	scanf("%d",&x);
	int conta=contalis(lis, x);
	int sommapos=sommalis(lis,x);
	printf("conta:%d\n",conta);
	printf("somma:%d\n",sommapos);
	return 0;
}
