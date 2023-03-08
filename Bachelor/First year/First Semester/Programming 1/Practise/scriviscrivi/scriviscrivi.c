#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#define dim 200

	

void scrivi(FILE *f,char nome[])
{
	FILE *g=fopen(nome,"r");
	if(g==NULL)
	{
		fprintf(f,"il file %s non esiste\n",nome);
		return;
	}
	char *riga,s[dim];
	while(true)
	{
		riga=fgets(s,dim,g);
		if(riga==NULL)
		break;
		fprintf(f,"%s\n",s);
	}
	fclose(g);
	return;
}

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("inserire più di due valori\n");
		return 1;
	}
	char nome[dim];
	for(int i=1;i<argc;i++)
		strcat(nome,argv[i]);
	FILE *f=fopen(nome,"w");
	if(f==NULL)
	{
		printf("impossibile creare il file\n");
		return 1;
	}
	for(int i=1;i<argc;i++)
		scrivi(f,argv[i]);
	fclose(f);
	return 0;
}
