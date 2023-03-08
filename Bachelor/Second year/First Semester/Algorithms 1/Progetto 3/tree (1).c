#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#include"tree.h"

void getData(student *d, FILE *f)
{
    fscanf(f,"%ld",&d->number);
    fscanf(f,"%s",d->name);
    fscanf(f,"%s",d->surname);
}

void copyStudent(student *d, student e)
{
    d->number=e.number;
    strcpy(d->name,e.name);
    strcpy(d->surname,e.surname);
}

tree initialize(char fileName[],int n, long *a)
{
    FILE *f=fopen(fileName,"r");
    if(f==NULL)
    {
        printf("Impossibile aprire file\n");
        exit(1);
    }
    tree t=NULL;
    a=(long *)malloc(n*sizeof(long));
    if(a==NULL)
    {
        printf("Errore allocazione\n");
        exit(1);
    }
    for(int i=0;i<n && !feof(f); i++)
    {
        student d;
        getData(&d,f);
        t=insertion(t,d);
        a[i]=d.number;
    }
    fclose(f);
    return t;
}

tree insertion(tree t, student d)
{
    if(t==NULL) t=newNode(d);
    else if(d.number<t->d.number) t->left=insertion(t->left,d);
    else t->right=insertion(t->right,d);
    return t;
}

tree newNode(student d)
{
    tree t=(node *)malloc(sizeof(node));
    if(t==NULL)
    {
        printf("Errore allocazione\n");
        exit(1);
    }
    copyStudent(&t->d,d);
    return t;
}

void normalSearch(tree t,long num, int *r)
{
    if(t==NULL) *r=0;
    else if(t->d.number==num) (*r)+=1;
    else
    {
        normalSearch(t->left,num,++r);
        normalSearch(t->right,num,++r);
    }
}

int searchABR(tree t, long num)
{
    if(t==NULL) return 0;
    else if(t->d.number==num) return 1;
    else if(t->d.number>num) return 1+searchABR(t->left,num);
    else return 1+searchABR(t->right, num);
}



