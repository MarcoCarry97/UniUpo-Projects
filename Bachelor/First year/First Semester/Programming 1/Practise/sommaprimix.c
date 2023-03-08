#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

void stampa(int a[],int num,int conta)
{
	for(int i=0;i<conta;i++)
		printf("%d\n",a[i]);
	return;
}

char primo(int num)
{
	if(num<2)
		return false;
	else if(num%2==0)
	{
		if(num==2)
			return true;
		else
			return false;
	}
	else
	{
		for(int i=3;i<num;i=i+2)
			if(num%i==0)
				return false;
	}
	return true;
}

int quanti(int a[], int n, int k)
{
  int q=0;
  for(int i=0;i<n;i++)
    if(a[i]==k) q++;
  return q;
}

int *nodup(int a[], int n, int *lungh)
{
  int *x = (int *) malloc(n*sizeof(int));
  assert(x!=NULL);
  int numel=0;
  for(int i=0;i<n;i++) 
  {
    int candidato = a[i];
    if(quanti(x,numel,candidato)==0)
	{
      x[numel] = candidato;
      numel +=1;
    }
  }
  x = (int *) realloc(x,numel*sizeof(int));
  *lungh = numel;
  return x;       
}

void sommaprimix(int vet[],int dim)
{
	int primi[dim],conta=0;
	for(int j=0;j<dim;j++)
		for(int i=0;i<dim;i++)
		{
			if(vet[i]!=0 || vet[j]!=0)
			{
				int somma=vet[i]+ vet[j];
				if(primo(somma))
				{
					printf("numero %d:%d   c=%d\n",i,somma,conta);
					primi[conta++]=somma;
				}
			}
		}
	int lung;
	int *senzadup=nodup(primi,dim,&lung);
	stampa(senzadup,dim,lung);
	printf("conta=%d\n",conta);
	free(senzadup);
	return;
}

int main(int argc,char *argv[])
{
	if(argc<=2)
	{
		printf("inserire piu' valori\n");
		return 1;
	}
	int vet[argc-1];
	for(int i=1;i<argc-1;i++)
		vet[i]=atoi(argv[i]);
	sommaprimix(vet,argc-1);
	return 0;
}

