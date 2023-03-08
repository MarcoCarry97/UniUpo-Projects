#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define SIZE 20
#define HASHSIZE 100

typedef struct data
{
	long id;
	char name[SIZE];
	char surname[SIZE];
}data;

typedef struct node
{
	data d;
	struct node *next;
}
typedef node *list;

void getData(data *d,FILE *f);
void copyData(data *d, data e);
int hashInsert(list t[], student e, int m);
int hashSearch(list t[], int e, int m, int *cont);
int h2(int k, int m);
int h1(int k, int m);
int h(int k, int i, int m);

int main()
{
	int n;
	int stress=60;
	list *ht= (node *)malloc(HASHSIZE*sizeof(node));
	assert(ht!=NULL);
	FILE *f=fopen("student.txt","r");
	assert(f!=NULL);
	int y=o;
	student d;
	while(stress<=80)
	{
		getData(&d,f);
		bool end=false;
		while(!feof(f))
		{
			y=hashInsert()
	}
}

void getData(data *d,FILE *f)
{
	fscanf(f,"%ld",&d->id);
	fscanf(f,"%s",&d->name);
	fscanf(f,"%s",&d->surname);
}

void copyData(data *d, data e)
{
	d->id=e.id;
	strcpy(d->name,e.name);
	strcpy(d->surname,e.surname);
}

int hashInsert(bucket t[], student e, int m)
{
	puts("ENTRO");
    int i,j;
    i=0;
    do{
		puts("ENTRO DO");
        j= h(e.id, i, m);
        if(t[j]==NULL)
        {
			puts("ENTRO IF");
            copy_data(&t[j]->d,e);
            puts("COPIATO");
            return j;
        }
        else i++;
        puts("ESCO DO");
    }while(i!=m);
    puts("ESCO");
    return -1;
}

int hashSearch(bucket t[], int e, int m, int *cont)
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
