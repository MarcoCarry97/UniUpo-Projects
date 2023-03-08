#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "tree.h"

#define max(x, y) (((x)>(y)) ? (x) : (y))

void visitDFS(tree t)
{
    if(t!=NULL)
    {
        printf("%d\n", t->d);
        visitDFS(t->left);
        visitDFS(t->right);
    }
}

void visitBFS(tree t)
{
    queue q;
    makeQueue(&q);
    enQueue(&q, t);
    while(!isEmptyQueue(q))
    {
        tree w = deQueue(&q);
        if(w != NULL)
        {
            printf("%d", w->d);
            visitBFS(w->left);
            visitBFS(w->right);
        }
    }
}

int height(tree t)
{
	if (t == NULL) return -1;
	else return 1 + max(height(t->left), height(t->right));
}

int numNodes(tree t)
{
    if(t==NULL) return 0;
	else return 1+numNodes(t->left) + numNodes(t->right);
}

int numLeaf(tree t)
{
    if(t==NULL) return 0;
	else if(t->left==NULL && t->right==NULL) return 1;
	else return numLeaf(t->left) + numLeaf(t->right);
}

tree newBranch(int d)
{
    tree t = (branch *)malloc(sizeof(branch));
	if (t == NULL)
	{
		perror("Errore allocazione");
		exit(1);
	}
	t->left = NULL;
	t->right = NULL;
	t->d = d;
	return t;
}

tree newTree(int n)
{
    if(n<=0) return NULL;
    else
    {
        tree t = newBranch(n);
        t->left=newTree((n-1)/2);
        t->right=newTree((n-1-((n-1)/2)));
    }
}

void makeQueue(queue *q)
{
	q->first = NULL;
	q->last = NULL;
}

void enQueue(queue *q, tree d)
{
    list l=NULL;
	inserisci(d,&l);
	if(isEmptyQueue((*q))) q->first = l;
    else q->last->next = l;
    q->last = l;
}

tree deQueue(queue *q)
{
	disposeHead(&q->first);
}

void inserisci(tree t,list  *l){
	list l1;
	makeList(&l1);
	l1 = (node *)malloc(sizeof(node));
	if (l1 != NULL)
    {
	  l1 -> d= t;
	  l1 ->next = (*l);
       (*l) = l1;
    }
}

void makeList(list *l)
{
    (*l)=NULL;
}

bool isEmptyQueue(queue q)
{
	return isEmptyList(q.first);
}

bool isEmptyList(list l)
{
	return l == NULL;
}

void disposeHead(list *l)
{
    list p=(*l);
    (*l)=(*l)->next;
    free(p);
}
