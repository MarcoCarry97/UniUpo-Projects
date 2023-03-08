#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

#define dim 100

char *formastri(char stri[],int num)
{
	char *neo=(char *)malloc(num*sizeof(char));
	snprintf(neo,dim,"");
	for(int i=0;i<=num;i++)
	{
		neo[i]=stri[i];
		neo[i+1]=0;
	}
	return neo;
}

char *prefissi(char stri[])
{
	char *pref=(char *)malloc(dim*sizeof(char));
	snprintf(pref,dim,"");
	for(int i=0;i<strlen(stri);i++)
	{
		char *sup=formastri(stri,i);
		
		strcat(pref,sup);
		strcat(pref," ");
		free(sup);
		
	}
	return pref;
}

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("Inserire solo un argomento\n");
		return 1;
	}
	char *pref=prefissi(argv[1]);
	printf("%s\n",pref);
	free(pref);
	return 0;
}
