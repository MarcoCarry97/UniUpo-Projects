#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

void sottostringhe(char stri[],int num)
{
	if(strlen(stri)<num)
	{
		puts("non esistono sottostringhe");
		return;
	}
	for(int i=0;i<strlen(stri)-num+1;i++)
	{
		char pezzo[num];
		int conta=0;
		for(int j=i;j<i+num;j++)
		{
			pezzo[conta++]=stri[j];
		}
		printf("%s\n",pezzo);
	}
	return;
}

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("inserire solo una stringa ed un valore intero\n");
		return 1;
	}
	sottostringhe(argv[1],atoi(argv[2]));
	return 0;
}

