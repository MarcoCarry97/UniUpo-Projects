#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct data
{
	int value;
	char seed;
}data;

typedef struct node
{
	data d;
	struct node *next;
}node;
typedef node *list;

typedef list stack;

typedef struct queue
{
	list first;
	list last;
}queue;

typedef struct branch
{
	data d;
	struct branch *left;
	struct branch *right;
}branch;
typedef branch *tree;

void inserisci(data el,list  *l); //Ho utilizzato questa per l'inserimento

void copyData(data *dest, data emit);
data putData(int value, char c);
bool equals(data d, data e);
void printData(data d);

void makeList(list *l);
bool isEmptyList(list l);
void insertHead(list *l, data d);
void insertTail(list *l,data d);
data disposeHead(list *l);
void disposeList(list *l);
data firstList(const list l);
void printList(list l);

void makeStack(stack *stk);
bool isEmptyStack(stack stk);
void push(stack *stk, data d);
data pop(stack *stk);
void disposeStack(stack *stk);
data top(const stack stk);

bool isEmptyQueue(queue q);
void makeQueue(queue *q);
void enQueue(queue *q, data d);
data deQueue(queue *q);
void disposeQueue(queue *q);
data firstQueue(const queue q);

/*tree makeTree(data d);
int heightTree(tree t);
bool isInTree(tree t, data d);
int numLeaves(tree t);
int numNodes(tree t);*/
