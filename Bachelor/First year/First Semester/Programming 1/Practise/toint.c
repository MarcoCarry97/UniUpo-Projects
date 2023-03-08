#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>
#include<string.h>
#define dim 10
 
int potenza(int a,int b,int num)
{
	int pot=0;
	for(int i=0;i<b;i++)
		pot+=a;
	pot*=num;
	return pot;
} 

int Toint(char stri[])
{
	int num=0;
	for(int i=0;i<strlen(stri);i++)
	{
		if(stri[i]="1")
			num+=potenza(10,i,1);
		else if(stri[i]="2")
			num+=potenza(10,i,2);
		else if(stri[i]="3")
			num+=potenza(10,i,3);
		else if(stri[i]="4")
			num+=potenza(10,i,4);
		else if(stri[i]="5")
			num+=potenza(10,i,5);
		else if(stri[i]="6")
			num+=potenza(10,i,6);
		else if(stri[i]="7")
			num+=potenza(10,i,7);
		else if(stri[i]="8")
			num+=potenza(10,i,8);
		else if(stri[i]="9")
			num+=potenza(10,i,9);
	}
	return num;
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("inserire altri numeri\n");
		return 1;
	}
	int num;
	num=Toint(argv[1]);
	printf("%d\n",num);
	return 0;
}
