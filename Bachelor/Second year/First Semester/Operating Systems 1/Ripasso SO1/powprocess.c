#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>
#include"xerrors.h"

#define BUFSIZE 100

long pot(long x,int y); //CALCOLA LA POTENZA X^Y

int main(int argc, char *argv[])
{
	if(argc!=4) //CONTROLLO INPUT
	{
		printf("Uso: %s fileName numFile numProcess\n",argv[0]);
		exit(0);
	}
	int numFile=atoi(argv[2]), numProcess=atoi(argv[3]);
	int idSem=xshmget(IPC_PRIVATE,3*sizeof(sem_t),0600,__LINE__,__FILE__); //SHM SEMAFORI
	sem_t *shmSem=(sem_t *)xshmat(idSem,NULL,0,__LINE__,__FILE__);
	sem_t *freeSlots=&shmSem[0], *dataItems=&shmSem[1], *bufMutex=&shmSem[2];
	xsem_init(freeSlots,1,BUFSIZE,__LINE__,__FILE__); //INIZIALIZZAZIONE SEMAFORI
	xsem_init(dataItems,1,0,__LINE__,__FILE__);
	xsem_init(bufMutex,1,1,__LINE__,__FILE__);
	int idBuffer=xshmget(IPC_PRIVATE,(BUFSIZE+1)*sizeof(int),0600,__LINE__,__FILE__);//SHM BUFFER
	int *buffer=(int *)xshmat(idBuffer,NULL,0,__LINE__,__FILE__);
	int *consIndex=buffer + BUFSIZE; //INDICE CONSUMATORI
	(*(consIndex))=0; 
	pid_t pid;
	for(int i=0;i<numProcess;i++) //CREAZIONE PROCESSI
	{
		//printf("Creo process\n");
		pid=xfork(__LINE__,__FILE__);
		if(pid==0) //CODICE PROCESSI CONSUMATORI
		{
			char fileName[100];
			int esp=0;
			bool endProcess=false;
			while(!endProcess)
			{
				//printf("%d consuma\n",getpid());
				xsem_wait(dataItems,__LINE__,__FILE__);
				xsem_wait(bufMutex,__LINE__,__FILE__);
				esp=buffer[(*(consIndex))]; //PRENDO DAL BUFFER
				(*(consIndex))=((*(consIndex))+1)%BUFSIZE;
				xsem_post(bufMutex,__LINE__,__FILE__);
				xsem_post(freeSlots,__LINE__,__FILE__);
				if(esp==-1) endProcess=true;
				else //CREO FILE CON POTENZE DI ESP
				{
					//printf("creo file %d\n",esp);
					long num=0;
					FILE *in=xfopen(argv[1],"r",__LINE__,__FILE__);
					bool endFile=false;
					sprintf(fileName,"%s.%d",argv[1],esp); 
					FILE *out=xfopen(fileName,"w",__LINE__,__FILE__);
					while(!endFile) //FINCHé FILE INPUT NON é FINITO
					{
						fscanf(in,"%ld",&num);
						if(feof(in)) endFile=true;
						else fprintf(out,"%ld\n",pot(num,esp)); 
					}
					fclose(out); //CHIUSURA FILE
					fclose(in);
				}
			}
			exit(0);
		}
	}
	int prodIndex=0; //CODICE PROCESSO PRODUTTORE
	for(int i=1;i<=numFile;i++) //PRODUCO VALORI E LI INSERISCO NEL BUFFER
	{
		//printf("produco\n");
		xsem_wait(freeSlots,__LINE__,__FILE__);
		buffer[prodIndex]=i;
		prodIndex=(prodIndex+1)%BUFSIZE;
		xsem_post(dataItems,__LINE__,__FILE__);
	}
	for(int i=0;i<numProcess;i++) //SEGNALO TERMINE DEL PRODUTTORE
	{
		//printf("termine\n");
		xsem_wait(freeSlots,__LINE__,__FILE__);
		buffer[prodIndex]=-1;
		prodIndex=(prodIndex+1)%BUFSIZE;
		xsem_post(dataItems,__LINE__,__FILE__);
	}
	//printf("aspetto\n");
	for(int i=0;i<numProcess;i++) //ATTENDO I PROCESSI CONSUMATORI
		pid=xwait(NULL,__LINE__,__FILE__);
	//printf("cancello\n");
	xshmdt(buffer,__LINE__,__FILE__); //DEALLOCO SHM
	xshmdt(shmSem,__LINE__,__FILE__);
	xshmctl(idBuffer,IPC_RMID,NULL,__LINE__,__FILE__);
	xshmctl(idSem,IPC_RMID,NULL,__LINE__,__FILE__);
	return 0;
}

long pot(long x, int y)
{
	long ret=1;
	for(int i=0;i<y;i++)
		ret*=x;
	return ret;
}
