#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void stampariga(char nome[], int num)
{
	FILE *f=fopen(nome,"r");
	char stri[100],*riga;
	int i=1;
	while(riga!=NULL && num>=i)
	{
		riga=fgets(stri,100,f);
		i++;
	}
	printf("%s\n",stri);
	fclose(f);
}

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("inserire una parola ed un numero\n");
		return 1;
	}
	stampariga(argv[1],atoi(argv[2]));
	return 0;
}

