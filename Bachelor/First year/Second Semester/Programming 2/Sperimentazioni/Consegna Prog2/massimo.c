#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>

void massimo(int a, int b,int *max)
{
	if(a>b)
		*max=a;
	else
		*max=b;
}

int main()
{
	int num1, num2;
	printf("inserire primo numero\n");
	scanf("%d",&num1);
	printf("inserire secondo numero\n");
	scanf("%d",&num2);
	int max;
	massimo(num1,num2,&max);
	printf("il massimo e' %d\n", max);
	return 0;
}
