#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#define dim 10

int trova(char s[],int num)
{
	int conta=0;
	int lunghezza=strlen(s);
	for(int i=0;i<lunghezza;i++)
	{
		if(s[i]==num)
			conta++;
		i++;
	}
	return conta;
}

void stampa(int a[],int num)
{
	for(int i=0;i<num;i++)
		printf("%d\n",a[i]);
	return;
}

void occorrenze(char stri[])
{
	FILE *f=fopen(stri,"r");
	char s[dim];
	int freq[dim];
	int i=65;
	char *riga;
	while(true)
	{
		while(i>=65 &&i<=90 && i>=97 && i<=122)
		{
			riga=fgets(s,dim,f);
			if(riga==NULL)
				break;
			freq[i]=trova(s,i);
		}
		i++;
		rewind(f);
		if(i==123)
			break;
	}
	fclose(f);
	stampa(freq,dim);
	return;
}

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("inserire un solo valore\n");
		return 1;
	}
	occorrenze(argv[1]);
	return 0;
}

