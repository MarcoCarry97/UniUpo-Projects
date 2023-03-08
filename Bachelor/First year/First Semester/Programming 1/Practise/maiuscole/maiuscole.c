#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#define dim 100

bool controlla(char str[], char lettere[])
{
	bool trovato=false;
	for(int i=0;i<strlen(str);i++)
	{
		for(int j=0;j<strlen(lettere);j++)
		{
			if(str[i]==lettere[j])
			{
				trovato=true;
				break;
			}
		}
		if(trovato==true)
			break;
	}
	return trovato;
}

bool *maiuscole(char nome[], int *k)
{
	FILE *f=fopen(nome,"r");
	if(f==NULL)
	{
		printf("file non presente\n");
		*k=0;
		exit(1);
	}
	char *riga, stri[dim];
	int siz=10,i;
	bool *vet=(bool *) malloc(siz*sizeof(bool));	
	while(true)
	{
		riga=fgets(stri,dim,f);
		if(riga==NULL)
			break;
		vet[i++]=controlla(stri,"ABCDEFGHIJKLMNOPQRTUVWXYZ");
	}
	vet=(bool *) realloc(vet,i*sizeof(bool));
	*k=i;
	return vet;
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("inserire solo una stringa\n");
		return 1;
	}
	int size;
	bool *vet=maiuscole(argv[1],&size);
	for(int i=0;i<size;i++)
	{
		if(vet[i]==true)
			printf("si\n");
		else
			printf("no\n");
	}
	free(vet);
	return 0;
}
