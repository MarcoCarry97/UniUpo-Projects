#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//#include"data.h"
#include"list.h"

bool isEmptyList(list l)
{
    return l==NULL;
}

void makeList(list *l)
{
    (*l)=NULL;
}

list newNode()
{
    return (node *)malloc(sizeof(node));
}

card *putData(int value, char c)
{
    card *crd=(card *)malloc(sizeof(card));
    crd->value=value;
    crd->seed=c;
    return crd;
}

void insertHead(card c, list *l)
{
    list p=newNode();
    p.c=c;
    p->next=(*l);
    (*l)=p;
}

void insertTail(card c, list *l)
{
    list n=(*l), tail=NULL;
    while(n!=NULL) n=n->next;
    list p=newNode();
    p->c=c;
    p->next=NULL;
    n->next=p;
}

void printData(card *c)
{
    printf("%c --- %d\n",c->seed, c->value);
}

void printList(list l)
{
    while(l!=NULL)
    {
        printData(l->c);
        l=l->next;
    }
}
