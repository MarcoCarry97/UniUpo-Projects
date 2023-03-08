#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

#define SIZE 30
#define RUN 10

typedef struct data
{
    long number;
    char name[SIZE];
    char surname[SIZE];
}student;

typedef struct node
{
    student d;
    struct node *left;
    struct node *right;
}node;

typedef node *tree;

void getStudent(student *d,FILE *f);
void copyStudent(student *d, student e);
tree insertion(tree t,student d);
tree newNode(student d);
tree initialize(char fileName[],int n, long *a);
void normalSearch(tree t, long num, int *r);
int searchABR(tree t, long num);
