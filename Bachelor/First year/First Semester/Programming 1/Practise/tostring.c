#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>
#include<string.h>
#define dim 10
 
char *Tostring(int num)
{
	char *stri=(char *) malloc(dim*sizeof(char));
	snprintf(stri,dim,"%d\n",num);
	return stri;	
}

int main()
{
	int num;
	char *stri;
	scanf("%d",&num);
	stri=Tostring(num);
	printf("%s\n",stri);
	return 0;
}
