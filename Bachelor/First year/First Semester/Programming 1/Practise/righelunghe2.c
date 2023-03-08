#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#define dim 100


void righelunghe(char stri[])
{
	int max;
	char parola[dim];
	FILE *f=fopen(stri,"r");
	if(f==NULL)
	{
		printf("file non trovato\n");
		exit(1);
	}
	char *riga;
	while(true)
	{
		riga=fgets(parola,dim,f);
		if(riga==NULL)
			break;
		if(strlen(parola)>max)
			max=strlen(parola);
	}
	rewind(f);
	char *nome=(char *) malloc(dim*sizeof(char));
	snprintf(nome,dim,"%slunghe.txt",stri);
	
	FILE *g=fopen(nome,"w");
	if(g==NULL)
	{
		printf("file non creato\n");
		exit(1);
	}
	while(true)
	{
		riga=fgets(nome,dim,f);
		if(riga==NULL)
			break;
		if(strlen(nome)==max)
			fprintf(g,"%s\n",nome);
	}
	free(nome);
	fclose(g);
	fclose(f);
	return;
}

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("inserire un solo valore");
		return 1;
	}
	righelunghe(argv[1]);
	return 0;
}
