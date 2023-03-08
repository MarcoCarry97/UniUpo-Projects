#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#define dim 100

void sommafile(char stri[])
{
	char *nome=(char*) malloc(dim*sizeof(char));
	snprintf(nome,dim,"%s.somme.txt",stri);
	FILE *f=fopen(stri,"r");
	FILE *g=fopen(nome,"w");
	char *riga,str[dim];
	int somma=0;
	while(true)
	{
		riga=fgets(str,dim,f);
		if(riga==NULL)
			break;
		somma+=atoi(str);
		fprintf(g,"%d\n",somma);
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
	sommafile(argv[1]);
	return 0;
}
