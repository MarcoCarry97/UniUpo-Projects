#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
int fattoriale(int n);
int fattoriale(int n)
{
	int fatt=1;
	for(int i=1;i<=n;i++)
		fatt*=i;
	return fatt;
}
int main(int argc, char *argv[])
{	
	assert(argc>1);
	int somma=0;
	for(int i=0;i<argc;i++)
		somma+=fattoriale(atoi(argv[i]));
	return 0;
}
