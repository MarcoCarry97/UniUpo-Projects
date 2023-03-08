#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
 
int main()
{
	int k;
	printf("inserire numero del mese:\n");
	scanf("%d",&k);
	switch(k)
	{
		int n;
		case(1):
			printf("inverno");
			break;
		case(2):
			printf("inverno");
			break;
		case(3):
			printf("inserire giorno del mese:\n");
			scanf("%d",&n);
			if(n>1 && n<20)
				printf("inverno");
			else
				printf("primavera");
			break;
		case(4):
			printf("primavera");
			break;
		case(5):
			printf("primavera");
			break;
		case(6):
			printf("inserire giorno del mese:\n");
			scanf("%d",&n);
			if(n>1 && n<20)
				printf("inverno");
			else
				printf("primavera");
			break;
		case(7):
			printf("estate");
			break;
		case(8):
			printf("estate");
			break;
		case(9):
			printf("inserire giorno del mese:\n");
			scanf("%d",&n);
			if(n>1 && n<20)
				printf("inverno");
			else
				printf("primavera");
			break;
		case(10):
			printf("autunno");
			break;
		case(11):
			printf("autunno");
			break;
		case(12):
			printf("inserire giorno del mese:\n");
			scanf("%d",&n);
			if(n>1 && n<20)
				printf("inverno");
			else
				printf("primavera");
			break;
	}
	return 0;
}

