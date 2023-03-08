#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"structure.h"

void copyData(data *dest, data emit)
{
	dest->value=emit.value;
	dest->seed=emit.seed;
}

data putData(int value, char c)
{
	data d;
	d.value=value;
	d.seed=c;
	return d;
}

bool isEmptyList(list l)
{
	return l == NULL;
}

list newNode()
{
	list l = (node *)malloc(sizeof(node));
	if (l == NULL)
	{
		perror("Errore Allocazione");
		exit(1);
	}
	else return l;
}

void insertHead(list *l, data d)
{
	list n = newNode();
	copyData(&n->d, d);
	n->next = (*l);
	(*l) = n;
}

void insertTail(list *l, data d)
{
	list n=(*l);
	while(n!=NULL) n=n->next;
	list p=newNode();
	copyData(&p->d,d);
	p->next=NULL;
	n->next=p;
}

data disposeHead(list *l)
{
	data d;
	if (!isEmptyList((list)l))
	{
		copyData(&d, (*l)->d);
		list n = (*l);
		(*l) = (*l)->next;
		free(n);
	}
	return d;
}

void disposeList(list *l)
{
	while ((*l) != NULL) disposeHead(l);
}

data firstList(const list l)
{
	data d;
	if (!isEmptyList(l)) d=l->d;
	return d;
}

bool isEmptyStack(stack stk)
{
	return isEmptyList(stk);
}

void push(stack *stk, data d)
{
	insertHead(stk, d);
}

data pop(stack *stk)
{
	return disposeHead(stk);
}

void disposeStack(stack *stk)
{
	disposeList(stk);
}

data top(const stack stk)
{
	return firstList(stk);
}

bool isEmptyQueue(queue q)
{
	return isEmptyList(q.first);
}

void makeQueue(queue *q)
{
	q->first = NULL;
	q->last = NULL;
}

//Alla fine ho usato questa
void inserisci(data el,list  *l){
	list l1;
	makeList(&l1);
	l1 = (node *)malloc(sizeof(node));
	if (l1 != NULL) {
	  l1 -> d= el;
	  l1 ->next = (*l);
       (*l) = l1;
}}

void enQueue(queue *q, data d)
{
    list l=NULL;
	inserisci(d, &l);
	if(isEmptyQueue(*q))
	{
		(*q).first = l;
		(*q).last = l;

	} else {
		(*q).last->next = l;
		(*q).last = l;
	}
}


data deQueue(queue *q)
{
	return disposeHead(&(q->first));
}

void disposeQueue(queue *q)
{
	disposeList(&(q->first));
}

data firstQueue(const queue q)
{
	return firstList(q.first);
}

void makeList(list *l)
{
    (*l)=NULL;
}

void makeStack(stack *stk){
	return makeList(stk);
}

//Ho aggiunto queste due funzioni per stampare
void printData(data d)
{
    printf("%d-%c\n",d.value, d.seed);
}

void printList(list l)
{
    while(l!=NULL)
    {
        printData(l->d);
        l=l->next;
    }
}

/*
tree newBranch()
{
	tree t = (branch *)malloc(sizeof(branch));
	if (t == NULL)
	{
		perror("Errore allocazione");
		exit(1);
	}
	else return t;
}

tree makeTree(data d)
{
	tree t = newBranch();
	copyData(&t->d, d);
	t->left = NULL;
	t->right = NULL;
	return t;
}

int heightTree(tree t)
{
	if (t == NULL) return -1;
	else return 1 + max(heightTree(t->left), heightTree(t->right));
}

bool isInTree(tree t, data d)
{
	if (t == NULL) return false;
	else if (equals(t->d, d)) return true;
	else if (isInTree(t->left),d) return true;
	else if (isInTree(t->right),d) return true;
	else return false;
}

int numLeaves(tree t)
{
	if(t==NULL) return 0;
	else if(t->left==NULL && t->right==NULL) return 1;
	else return numLeaves(t->left) + numLeaves(t->right);
}

int numNodes(tree t)
{
	if(t==NULL) return 0;
	else return 1+numNodes(t->left) + numNodes(t->right);
}
*/
