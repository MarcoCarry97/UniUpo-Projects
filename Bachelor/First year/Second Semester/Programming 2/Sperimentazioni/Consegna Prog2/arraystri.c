#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

char **matrice(int n,int m)
{
	char **mat=(char **)malloc(n*sizeof(char *));
	for(int i=0;i<n;i++)
	{
		mat[i]=(char *)malloc(m*sizeof(char));
		printf("Inserire caratteri uno alla volta\n");
		for(int j=0;j<m;j++)
		{
			//printf("inserire carettere %d nella riga %d:\n",j,i);
			scanf("%s",&mat[i][j]);
		}
	}
	return mat;
}

void stampa(char *mat[],int num)
{
	for(int i=0;i<num;i++)
		printf("%s\n",mat[i]);
}

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("inserire almeno due valori interi\n");
		return 1;
	}
	char **mat=matrice(atoi(argv[1]),atoi(argv[2]));
	stampa(mat,atoi(argv[1]));
	free(mat);
	return 0;
}
