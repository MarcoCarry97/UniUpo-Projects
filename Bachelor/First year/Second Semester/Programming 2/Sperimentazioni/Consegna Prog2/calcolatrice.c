#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>

void calcolatrice(int a, int b,int *add,int *sub,int *mul, float *div, float *rad)
{
	*add=a+b;
	*sub=a-b;
	*mul=a*b;
	*div=a/b;
	int aq=pow(a,2), bq=pow(b,2);
	*rad=sqrt(aq+bq);
}

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("inserire due numeri interi positivi");
		return 1;
	}
	int somma=0, diff=0, prod=0;
	float quoz=0,rad=0;
	calcolatrice(atoi(argv[1]),atoi(argv[2]),&somma,&diff,&prod,&quoz,&rad);
	printf("somma: %d\n",somma);
	printf("differenza: %d\n",diff);
	printf("prodotto: %d\n",prod);
	printf("quoziente: %.2f\n",quoz);
	printf("radice: %.3f\n",rad);
	return 0;
}
