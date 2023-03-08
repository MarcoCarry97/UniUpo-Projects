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

int main()
{
	return 0;
}
