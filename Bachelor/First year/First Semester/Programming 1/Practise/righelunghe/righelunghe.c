#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#define dim 100

int maxfile(char nome[])
{
	FILE *f=fopen(nome,"r");
	char stri[dim],*riga;
	int max;
	while(true)
	{
		riga=fgets(stri,dim,f);
		if(riga==NULL)
			break;
		if(strlen(riga)>max)
			max=strlen(riga);
	}
	fclose(f);
	return max;
}

void righelunghe(char stri[])
{
	int max=maxfile(stri);
	char *nome=(char*) malloc(dim*sizeof(char));
	snprintf(nome,dim,"%slunghe.txt",stri);
	FILE *f=fopen(stri,"r");
	FILE *g=fopen(nome,"w");
	char *riga;
	while(true)
	{
		char parola[dim];
		fscanf("%s",&parola);
		riga=fgets(parola,dim,f);
		if(riga==NULL)
			break;
		if(strlen(parola)==max)
			fprintf(g,"%s\n",parola);
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
