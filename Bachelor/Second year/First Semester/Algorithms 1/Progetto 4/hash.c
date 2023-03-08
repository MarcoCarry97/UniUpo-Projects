#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    long id;
    char nome[40];
    char cognome[40];
}student;

typedef struct data
{
    student d;
    struct data *next;
}data;

typedef data *bucket;

int hash_insert(bucket t[], student e, int m);
int hash_search(bucket t[], int e, int m, int *cont);
void copy_data(student *dest, student emit);
int h(int k, int i, int m);
int h1(int k, int m);
int h2(int k, int m);

int main(int argc, char *argv[])
{
    int carico = 60;
    int n; //numero di studenti da gestire
    char nome[30];
    strcpy(nome, "studenti.txt");
    int m = 100; //dimensione tabella di hash
    do{
        n = (carico*m)/100;
        bucket *list= (bucket *)malloc(m*sizeof(bucket));
        bucket *linescan= (bucket *)malloc(m*sizeof(bucket));
        bucket *ht= (bucket *)malloc(m*sizeof(bucket));  //tabella creata dinamicamente
        carico+=10;
    }while(carico<=100);
    return 0;
}

int hash_insert(bucket t[], student e, int m)
{
    int i,j;
    i=0;
    do{
        j= h(e.id, i, m);
        if(t[j]==NULL)
        {
            t[j]->d = e;
            return j;
        }
        else
            i++;
    }while(i!=m);
    return -1;
}

int hash_search(bucket t[], int e, int m, int *cont)
{
    int i,j;
    i=0;
    do{
        j = h(e, i, m);
        if((t[j]->d.id) == e) return j;
        else i++;
        (*cont)++;
    }while((t[j] != NULL) && (i!=m));
    return -1;
}

void copy_data(student *dest, student emit)
{
    dest->id = emit.id;
    strcpy(dest->nome, emit.nome);
    strcpy(dest->cognome, emit.cognome);
}

int h1(int k, int m)
{
    return(k%m);
}

int h2(int k, int m)
{
    return(k%(m-1)+1);
}

int h(int k, int i, int m)
{
    return((h1(k,m) + i*h2(k,m)) %m);
}
