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
		printf("Uso: %s fileName size\n",argv[0]);
		exit(0);
	}
	int size=atoi(argv[2]);
	int *a=(int *)malloc(size*sizeof(int));
	if(a==NULL)
	{
		perror("Errore allocazione");
		exit(2);
	}
	for(int i=0;i<size;i++) a[i]=i+1;
	//for(int i=0;i<size;i++) printf("%d\n",a[i]);
	int f=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0600);
	if(f==-1)
	{
		perror("Errore apertura file");
		exit(1);
	}
	int e=write(f,a,size*sizeof(int));
	if(e<size*sizeof(int))
	{
		perror("Errore scrittura");
		exit(3);
	}
	e=close(f);
	if(e==-1)
	{
		perror("Errore chiusura");
		exit(4);
	}
	free(a);
	return 0;
}
