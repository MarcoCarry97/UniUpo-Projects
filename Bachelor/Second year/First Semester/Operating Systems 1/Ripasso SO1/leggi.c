#include <stdio.h>    // permette di usare scanf printf .. 
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("Uso: %s fileName blockSize",argv[0]);
		exit(0);
	}
	int blockSize=atoi(argv[2]);
	long sum=0;
	int f=open(argv[0],O_RDONLY);
	if(f<0)
	{
		perror("Errore apertura file");
		exit(1);
	}
	int e=0;
	bool end=false;
	while(!end)
	{
		int *a=(int *)malloc(blockSize*sizeof(int));
		if(a==NULL)
		{
			perror("Errore allocazione");
			exit(2);
		}
		for(int i=0;i<blockSize;i++) a[i]=0;
		e=read(f,a,blockSize*sizeof(int));
		printf("--------------------------\n");
		for(int i=0;i<blockSize;i++) printf("a: %d\n",a[i]);
		if(e==0) end=true;
		else if(e==-1)
		{
			perror("Errore lettura");
			exit(2);
		}
		else for(int i=0;i<e/sizeof(int);i++) sum+=a[i];
		free(a);
	}
	e=close(f);
	if(e==-1)
	{
		perror("errore chiusura file");
		exit(3);
	}
	printf("Somma: %ld\n",sum);
	return 0;
}
