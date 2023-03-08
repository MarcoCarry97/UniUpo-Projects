#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

bool primo(int n)
{
    if(n<2) 
        return false;
    else if(n%2==0) 
	{ 
        if(n==2)
			return true;
        else      
			return false;
    }
    else
	{
        assert(n%2!=0);
        for(int i=3;i < n; i+=2)
		{
            if(n%i==0)
				return false;
            if(i*i > n)
            	break;
        }
        return true;
    }
}

int *tra2primi(int vet[], int n, int *k)
{
	int *a=(int *)malloc (n*sizeof(int));
	if(a==NULL)
	{
		printf("Memoria insufficiente\n");
		*k=0;
		return NULL;
	}
	int conta=0;
	for(int i=0; i<n; i++)
		if(primo(vet[i-1]) && primo(vet[i+1]))
			a[conta++]=vet[i];
	*k=conta;
	a=(int *)realloc (a,conta*sizeof(int));
	return a;	
}

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("Inserisci almeno due valori");
		return 1;	
	}
int vet[argc],siz;
for(int i=0; i<argc; i++)
	vet[i]=atoi(argv[i]);
int *a= tra2primi(vet,argc,&siz);
printf("dimensione: %d\n",siz);
for(int i=0; i<siz; i++)
	printf("%d\n", a[i]);
free(a);
return 0;		
}


