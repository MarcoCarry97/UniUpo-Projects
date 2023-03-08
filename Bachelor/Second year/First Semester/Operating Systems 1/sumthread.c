//MARCO CAREGA 20018128
#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<pthread.h>
#include<semaphore.h>
#include"xerrors.h"

// Es1: uso non corretto della cond variable + mutex, il resto OK
// Es2: alcune imperfezioni nella realizzazione dello schema prod-cons

// voto: 28



typedef struct data
{
  FILE *file;
  int num;
  int numLine;
  volatile int *readLine;
  pthread_cond_t *cond;
  //pthread_cont_t *condMutex;
  pthread_mutex_t *fileMutex;
}data;

int lineCounter(char fileName[]);
void *tbody(void *arg);

int main(int argc, char *argv[])
{
  if(argc!=3)
  {
    printf("Uso:%s fileIn numLine\n",argv[0]);
    exit(0);
  }
  int numLine=atoi(argv[2]);
  int maxLine=lineCounter(argv[1]);
  int min=0;
  //\\ andava usata la condition variable per fermarsi  dopo numLine computazioni, ma doevano partire tutte!
  if(maxLine>numLine) min=numLine;
  else min=maxLine;
  
  pthread_t t[min];
  data d[min];
  char nameOut[100];
  snprintf(nameOut,100,"%s.somme",argv[1]);
  FILE *input=xfopen(argv[1],"r",__LINE__,__FILE__);
  pthread_mutex_t fileMutex, mutex;
  pthread_cond_t cond;
  xpthread_mutex_init(&fileMutex,NULL,__LINE__,__FILE__);
  xpthread_mutex_init(&mutex,NULL,__LINE__,__FILE__);
  xpthread_cond_init(&cond,NULL,__LINE__,__FILE__);
  FILE *output=xfopen(nameOut,"w",__LINE__,__FILE__);
  volatile int readLine=0;
  for(int i=0;i<min;i++)
  {
    d[i].file=output;
    d[i].numLine=min;//\\ ???
    d[i].readLine=&readLine; 
    fscanf(input,"%d",&d[i].num);
    d[i].fileMutex=&fileMutex;
    //d[i].condMutex=&mutex;  //\\ questo andava passato
    d[i].cond=&cond;
    //printf("creo thread\n");
    xpthread_create(&t[i],NULL,tbody,(void *) &d[i],__LINE__,__FILE__);
  }
  //printf("attendo\n");
  while(readLine<min)//\\ quando si chiama la wait bisogna avere il lock su mutex
    xpthread_cond_wait(&cond,&mutex,__LINE__,__FILE__);
  fclose(output);
  fclose(input);
  xpthread_mutex_destroy(&fileMutex,__LINE__,__FILE__);
}

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

void *tbody(void *arg)
{
  //printf("inizio thread\n");
  data *d=(data *) arg;
  //printf("numero dato: %d\n",d->num);
  int sumDiv=0;
  for(int i=1;i<=d->num;i++)
    if(d->num%i==0) sumDiv+=i;
  xpthread_mutex_lock(d->fileMutex,__LINE__,__FILE__);
  fprintf(d->file,"%d %d\n",d->num,sumDiv);
  (*(d->readLine))++;
  //\\ qui ci voleva il lock su mutex dedicato 
  xpthread_cond_signal(d->cond,__LINE__,__FILE__);
  xpthread_mutex_unlock(d->fileMutex,__LINE__,__FILE__);//\\ questo andava rilascato immediatamente dopo aver scritto sul file
  //printf("fine thread\n");
  pthread_exit(NULL);
}
