#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"data.h"

typedef struct data
{
    int value;
    char seed;
}card;

typedef struct node
{
    card *c;
    struct node *next;
}node;
typedef node *list;

void makeList(list *l);
void insertHead(card c, list *l);
void insertTail(card c, list *l);
bool isEmptyList(list l);
void printList(list l);
void putData(int value, char c);
