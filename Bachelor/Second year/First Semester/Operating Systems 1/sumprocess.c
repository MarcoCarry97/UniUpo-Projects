#define _GNU_SOURCE
#include<stdio.h>
#include<stdio.h>
#include<stdio.h>
#include"xerrors.h"

#define BUFSIZE 10

int lineCounter(char fileName[]);

int main(int argc, char *argv[])
{
  if(argc!=2)
  {
    printf("Uso:%s fileIn\n",argv[0]);
    exit(0);
  }
  int idSem=xshmget(IPC_PRIVATE,2*sizeof(sem_t),0600,__LINE__,__FILE__);
  sem_t *shmSem=(sem_t *)xshmat(idSem,NULL,0,__LINE__,__FILE__);
  sem_t *freeSlots=&shmSem[0];
  sem_t *dataItems=&shmSem[1];
  //sem_t *bufMutex=&shmSem[2];
  //sem_t *fileMutex=&shmSem[3];
  xsem_init(freeSlots,1,BUFSIZE,__LINE__,__FILE__);
  xsem_init(dataItems,1,0,__LINE__,__FILE__);
  //xsem_init(fileMutex,1,1,__LINE__,__FILE__);
  //xsem_init(bufMutex,1,1,__LINE__,__FILE__);
  int idBuf=xshmget(IPC_PRIVATE,(BUFSIZE+1)*sizeof(int),0600,__LINE__,__FILE__);
  int *buffer=(int *)xshmat(idBuf,NULL,0,__LINE__,__FILE__);
  int *consIndex=buffer +BUFSIZE;
  (*(consIndex))=0;
  pid_t pid;
  int numLine=lineCounter(argv[1]);
  char nameOut[100];
  snprintf(nameOut,100,"%s.somme",argv[1]);
  FILE *input=xfopen(argv[1],"r",__LINE__,__FILE__);
  FILE *output=xfopen(nameOut,"w",__LINE__,__FILE__);
  pid=xfork(__LINE__,__FILE__);
  if(pid==0)
  {
    bool end=false;
    while(!end)
    {
      int num=0, sumDiv=0;
      xsem_wait(dataItems,__LINE__,__FILE__);
      num=buffer[(*(consIndex))];
      (*(consIndex))=((*(consIndex))+1)%BUFSIZE;
      xsem_post(freeSlots,__LINE__,__FILE__);
      printf("Ho ricevuto %d (%d)\n",num, *consIndex);
      //\\ manca il break se num<0
      for(int i=1;i<=num;i++)
        if(num%i==0) sumDiv+=i;//\\ sumDiv andava azzerato
      fprintf(output,"%d %d\n",num,sumDiv);
    }
    fclose(output);
    exit(0);
  }
  int prodIndex=0;
  for(int i=0;i<numLine;i++)
  {
    int num=0;
    fscanf(input,"%d",&num);
    printf("Ho letto %d\n",num);    
    xsem_wait(freeSlots,__LINE__,__FILE__);
    buffer[prodIndex]=num;
    prodIndex =(prodIndex+1)%BUFSIZE; //\\ c'era += invece di =
    xsem_post(dataItems,__LINE__,__FILE__);
  }
  fclose(input);
  xsem_wait(freeSlots,__LINE__,__FILE__);
  buffer[prodIndex]=-1;
  prodIndex+=(prodIndex+1)%BUFSIZE;
  xsem_post(dataItems,__LINE__,__FILE__);
  xwait(NULL,__LINE__,__FILE__);
  xshmdt(buffer,__LINE__,__FILE__);
  xshmctl(idBuf,IPC_RMID,NULL,__LINE__,__FILE__);
  xshmdt(shmSem,__LINE__,__FILE__);
  xshmctl(idSem,IPC_RMID,NULL,__LINE__,__FILE__);
  return 0;
}

//\\ non serviva doveva leggere fino alla fine del file
int lineCounter(char fileName[])
{
  FILE *file=xfopen(fileName,"r",__LINE__,__FILE__);
  int numLine=0;
  char *line, s[100];
  bool end=false;
  while(!end)
  {
    //printf("conto linea\n");
    line=fgets(s,100,file);
    if(line==NULL) end=true;
    else numLine++;
  }
  fclose(file);
  return numLine;
}

// OK
//PARTE SUI SEGNALI: ATTESTATO
