#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct branch
{
    int d;
    struct branch *left;
    struct branch *right;
}branch;
typedef branch *tree;

typedef struct node
{
	tree d;
	struct node *next;
}node;
typedef node *list;

typedef struct queue
{
	list first;
	list last;
}queue;

void visitDFS(tree t);
void visitBFS(tree t);
int height(tree t);
int numNodes(tree t);
int numLeaf(tree t);
tree newBranch(int n);
tree newTree(int n);

void makeQueue(queue *q);
void enQueue(queue *q, tree d);
tree deQueue(queue *q);
void inserisci(tree t,list  *l);
void makeList(list *l);
bool isEmptyQueue(queue q);
bool isEmptyList(list l);
void disposeHead(list *l);
