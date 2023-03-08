#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

bool primo(int n)
{
    if(n<2) 
        return false;
    else if(n%2==0) 
	{ 
        if(n==2)
			return true;
        else      
			return false;
    }
    else
	{
        assert(n%2!=0);
        for(int i=3;i < n; i+=2)
		{
            if(n%i==0)
				return false;
            if(i*i > n)
            	break;
        }
        return true;
    }
}

int *primiab(int a,int b,int *n)
{
	int *vet=(int *)malloc(b*sizeof(int));
	int conta=0;
	for(int i=a;i<=b;i++)
		if(primo(i))
			vet[conta++]=i;
	vet=(int *)realloc(vet,conta*sizeof(int));
	*n=conta;
	return vet;
}

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("inserire più di due valori\n");
		return 1;
	}
	int a=atoi(argv[1]),b=atoi(argv[2]);
	int dim;
	int *vet=primiab(a,b,&dim);
	for(int i=0;i<dim;i++)
		printf("%d\n",vet[i]);
	free(vet);
	return 0;
}

