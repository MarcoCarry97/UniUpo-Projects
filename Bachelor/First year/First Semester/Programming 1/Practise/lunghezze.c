#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

int maiuscoli(char frase[],int num,char lettere[])
{
	int conta=0;
	for(int i=0;i<num;i++)
		for(int j=0;j<strlen(lettere);j++)
			if(frase[i]==lettere[j])
				conta++;
	return conta;
}

int minuscoli(char frase[],int num,char lettere[])
{
	int conta=0;
	for(int i=0;i<num;i++)
		for(int j=0;j<strlen(lettere);j++)
			if(frase[i]==lettere[j])
				conta++;
	return conta;
}

int *lunghezze(char *a[],int num, int *up, int *low)
{
	int *vet=(int *) malloc(num*sizeof(int));
	int kup=0,klow=0;
	for(int i=0;i<num;i++)
	{
		vet[i]=strlen(a[i]);
		kup+=maiuscoli(a[i],vet[i],"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		klow+=minuscoli(a[i],vet[i],"abcdefghijklmnopqrstuvwxyz");
	}
	*up=kup;
	*low=klow;
	return vet;
}

int main(int argc, char *argv[])
{
	if(argc<=2)
	{
		printf("inserire solo una stringa\n");
		return 1;
	}
	int up,low;
	int *lung=lunghezze(argv,argc,&up,&low);
	for(int i=1;i<argc;i++)
		printf("%d\n",lung[i]);
	printf("Maiuscoli: %d\n",up);
	printf("minuscoli: %d\n",low);
	free(lung);
	return 0;
}
