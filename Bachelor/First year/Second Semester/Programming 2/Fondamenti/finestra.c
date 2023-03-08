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

int finestra(LINK lis, int num)
{
	int conta=0;
	if(lis!=NULL)
		if(lis->next!=NULL)
			while(lis->next->next!=NULL)
			{
				if(num==lis->d && num==lis->next->d && num==lis->next->next->d)
					conta++;
				lis=lis->next;
			}
	return conta;
}

int main()
{
	LINK lis=crealista();
	int x;
	printf("inserire valore x\n");
	scanf("%d",&x);
	int conta=finestra(lis, x);
	printf("finestra:%d\n",conta);
	return 0;
}
