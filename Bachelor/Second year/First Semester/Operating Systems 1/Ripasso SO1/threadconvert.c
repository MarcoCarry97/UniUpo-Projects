#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#include<ctype.h>
#include<pthread.h>
#include<semaphore.h>
#include"xerrors.h"

#define BUFSIZE 10
#define LINESIZE 100

typedef struct data
{
	char *fileName;
	char **buffer;
	int *consIndex;
	sem_t *freeSlots;
	sem_t *dataItems;
}data;

void conversion(char line[]);
void *threadTwoBody(void *arg);
void *threadThreeBody(void *arg);

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("Uso: %s fileIn fileOut\n",argv[0]);
		exit(0);
	}
	FILE *input=xfopen(argv[1],"r",__LINE__,__FILE__);
	char line[LINESIZE];
	sem_t freeSlots, dataItems;
	xsem_init(&freeSlots,0,BUFSIZE,__LINE__,__FILE__);
	xsem_init(&dataItems,0,0,__LINE__,__FILE__);
	char **buffer=(char **)malloc(BUFSIZE*sizeof(char *));
	assert(buffer!=NULL);
	for(int i=0;i<BUFSIZE;i++)
	{
		buffer[i]=(char *)malloc(LINESIZE*sizeof(char));
		assert(buffer[i]!=NULL);
	}
	int consIndex=0;
	pthread_t t;
	data d;
	d.fileName=argv[2];
	d.buffer=buffer;
	d.consIndex=&consIndex;
	d.freeSlots=&freeSlots;
	d.dataItems=&dataItems;
	xpthread_create(&t,NULL,threadTwoBody, (void *) &d,__LINE__,__FILE__);
	bool end=false;
	int prodIndex=0;
	while(!end)
	{
		fgets(line,LINESIZE,input);
		if(feof(input)) end=true;
		else
		{
			xsem_wait(&freeSlots,__LINE__,__FILE__);
			strcpy(buffer[prodIndex],line);
			//printf("buffer main: %s",buffer[prodIndex]);
			prodIndex=(prodIndex+1)%BUFSIZE;
			xsem_post(&dataItems,__LINE__,__FILE__);
			//printf("%s",line);
		}
	}
	fclose(input);
	xsem_wait(&freeSlots,__LINE__,__FILE__);
	strcpy(buffer[prodIndex],"END");
	//printf("termine produttore 1\n");
	prodIndex=(prodIndex+1)%BUFSIZE;
	xsem_post(&dataItems,__LINE__,__FILE__);
	xpthread_join(t,NULL,__LINE__,__FILE__);
	printf("Thread 2 terminato\n");
	for(int i=0;i<BUFSIZE;i++) free(buffer[i]);
	free(buffer);
	return 0;
}

void conversion(char line[])
{
	for(int i=0;i<strlen(line);i++)
	{
		if(isupper(line[i])) line[i]=tolower(line[i]);
		else if(islower(line[i])) line[i]=toupper(line[i]);
	}
}

void *threadTwoBody(void *arg)
{
	//printf("thread 2\n");
	data *d=(data *) arg;
	sem_t freeSlots, dataItems;
	xsem_init(&freeSlots,0,BUFSIZE,__LINE__,__FILE__);
	xsem_init(&dataItems,0,0,__LINE__,__FILE__);
	char **buffer=(char **)malloc(BUFSIZE*sizeof(char *));
	assert(buffer!=NULL);
	for(int i=0;i<BUFSIZE;i++)
	{
		buffer[i]=(char *)malloc(LINESIZE*sizeof(char));
		assert(buffer[i]!=NULL);
	}
	int consIndex=0;
	pthread_t t;
	data e;
	e.fileName=d->fileName;
	e.buffer=buffer;
	e.consIndex=&consIndex;
	e.freeSlots=&freeSlots;
	e.dataItems=&dataItems;
	xpthread_create(&t,NULL,threadThreeBody,(void *) &e,__LINE__,__FILE__);
	int prodIndex=0;
	bool end=false;
	while(!end)
	{
		char line[LINESIZE];
		xsem_wait(d->dataItems,__LINE__,__FILE__);
		strcpy(line,d->buffer[(*(d->consIndex))]);
		//printf("buffer 2: %s",d->buffer[(*(d->consIndex))]);
		(*(d->consIndex))=((*(d->consIndex))+1)%BUFSIZE;
		xsem_post(d->freeSlots,__LINE__,__FILE__);
		//printf("line: %s",line);
		if(strcmp(line,"END")==0) end=true;
		else
		{
			conversion(line);
			//printf("convert: %s\n",line);
			xsem_wait(&freeSlots,__LINE__,__FILE__);
			strcpy(buffer[prodIndex],line);
			prodIndex=(prodIndex+1)%BUFSIZE;
			xsem_post(&dataItems,__LINE__,__FILE__);
		}
	}
	xsem_wait(&freeSlots,__LINE__,__FILE__);
	strcpy(buffer[prodIndex],"END");
	prodIndex=(prodIndex+1)%BUFSIZE;
	xsem_post(&dataItems,__LINE__,__FILE__);
	//printf("termine produttore 2\n");
	xpthread_join(t,NULL,__LINE__,__FILE__);
	printf("Thread 3 terminato\n");
	for(int i=0;i<BUFSIZE;i++) free(buffer[i]);
	free(buffer);
	pthread_exit(NULL);
}

void *threadThreeBody(void *arg)
{
	//printf("thread 3\n");
	data *d=(data *) arg;
	FILE *output=xfopen(d->fileName,"w",__LINE__,__FILE__);
	bool end=false;
	while(!end)
	{
		char line[LINESIZE];
		xsem_wait(d->dataItems,__LINE__,__FILE__);
		strcpy(line, d->buffer[(*(d->consIndex))]);
		(*(d->consIndex))=((*(d->consIndex))+1)%BUFSIZE;
		xsem_post(d->freeSlots,__LINE__,__FILE__);
		//printf("linea: %s\n",line);
		if(strcmp(line,"END")==0) end=true;
		else fprintf(output,"%s",line);
	}
	fclose(output);
	pthread_exit(NULL);
}

