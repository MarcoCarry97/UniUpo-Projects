#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#include<time.h>

#define SIZE 30

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
int normalSearch(tree t, long num);
int searchABR(tree t, long num);
void disposeTree(tree *t);

int main()
{
	srand(time(NULL));
	/*FILE *f=fopen("ris.csv","w");
	if(f==NULL)
	{
		printf("Impossibile creare file\n");
		return 0;
	}*/
	FILE *f=fopen("ris.csv","w");
	if(f==NULL)
	{
		printf("Impossibile creare file\n");
		return 0;
	}
	for(int run=1;run<=10000000;run*=10)
	{
		fprintf(f,"RUN = %d\n",run);
		for(int n=10;n<=80;n+=10)
		{
			//int n=10;
			//printf("num = %d\n",n);
			long normal=0,abr=0;
			long *a=(long *)malloc(n*sizeof(long));
			if(a==NULL)
			{
				printf("errore allocazione array\n");
				return 0;
			}
			tree t= initialize("studenti.txt",n,a);
			//printf("Albero inizializzato\n");
			/*for(int i=0;i<n;i++)
			{
				printf("posizione: %d\n",i);
				int normal=normalSearch(t,a[i]);
				int abr=searchABR(t,a[i]);
				fprintf(f,"%d,%d\n",normal, abr);
			}*/
			for(int i=0;i<run;i++)
			{
				int r=(int)rand()%n;
				//printf("Devo cercare la matricola in posizione %d nell'albero\n",r);
				//printf("ricerca normale\n");
				normal+=normalSearch(t,a[r]);
				//printf("ricerca normale\n");
				//printf("ricerca abr\n");
				r=(int)rand()%n;
				abr+=searchABR(t,a[r]);
				//printf("ricerca abr\n");
			}
			fprintf(f,"%ld,%ld\n",normal/run,abr/run);
			//fprintf(f,"%d\n",normal);
			//printf("scrittura su file\n");
			disposeTree(&t);
			//printf("elimino albero\n");
			free(a);
		}
	}
	fclose(f);
	return 1;
}

void copyStudent(student *d, student e)
{
	d->number=e.number;
	strcpy(d->name,e.name);
	strcpy(d->surname,e.surname);
}

tree newNode(student d)
{
	tree t=(node *)malloc(sizeof(node));
	if(t==NULL)
	{
		printf("errore allocazione nodo albero\n");
		exit(1);
	}
	t->left=NULL;
	t->right=NULL;
	copyStudent(&t->d,d);
	return t;
}

void getStudent(student *d,FILE *f)
{
	fscanf(f,"%ld",&d->number);
	fscanf(f,"%s",d->name);
	fscanf(f,"%s",d->surname);
}

tree insertion(tree t, student d)
{
	if(t==NULL) t=newNode(d);
	else if(d.number<t->d.number) t->left=insertion(t->left,d);
	else if(d.number>t->d.number) t->right=insertion(t->right,d);
	return t;
}

tree initialize(char fileName[], int n,long a[])
{
	FILE *f=fopen(fileName,"r");
	if(f==NULL)
	{
		//printf("file non trovato\n");
		exit(1);
	}
	tree t=NULL;
	/*a=(long *)malloc(n*sizeof(long));
	if(a==NULL)
	{
		printf("errore allocazione array\n");
		exit(1);
	}*/
	for(int i=0;i<n && !feof(f);i++)
	{
		student d;
		getStudent(&d,f);
		t=insertion(t,d);
		a[i]=d.number;
	}
	fclose(f);
	return t;
}

int normalSearch(tree t, long num)
{
	//printf("inizio\n");
	if(t==NULL)
	{
		//printf("non trovato\n");
		return 0;
	}
	else if(t->d.number==num) 
	{
		//printf("trovato\n");
		return 1;
	}
	int left=normalSearch(t->left,num);
	int right=normalSearch(t->right,num);
	return 1+left+right;
}

int searchABR(tree t, long num)
{
	int left=0, right=0;
	//printf("inizio ABR\n");
	if(t==NULL)
	{
		//printf("Non trovato\n");
		return 0;
	}
	else if(t->d.number==num)
	{
		//printf("trovato\n");
		return 1;
	}
	else if(t->d.number>num) left=searchABR(t->left,num);
	else right=searchABR(t->right,num);
	return 1+left+right;
}

void disposeTree(tree *t)
{
	if((*t)!=NULL)
	{
		disposeTree(&(*t)->left);
		disposeTree(&(*t)->right);
		//printf("cancella nodo\n");
		free((*t));
	}
}
