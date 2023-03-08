#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include"xerrors.h"

bool primo(int n);

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("Uso: %s limit processes\n",argv[0]);
		exit(0);
	}
	pid_t pid;
	int limit=atoi(argv[1]), processes=atoi(argv[2]);
	int shmid=xshmget(IPC_PRIVATE,processes*sizeof(int),0600,__LINE__,__FILE__);
	int *shm=xshmat(shmid,NULL,0, __LINE__,__FILE__);
	for(int i=0;i<processes;i++)
	{
		pid=xfork(__LINE__,__FILE__);
		if(pid==0)
		{
			int counter=0;
			for(int j=2*i+1;j<limit;j+=2*processes)
				if(primo(j)) counter++;
			shm[i]=counter;
			exit(0);
		}
	}
	for(int i=0;i<processes;i++) pid=xwait(NULL,__LINE__,__FILE__);
	int sum=0;
	for(int i=0;i<processes;i++) sum+=shm[i];
	printf("Numeri primi minori di %d trovati: %d\n", limit, sum);
	xshmdt(shm,__LINE__,__FILE__);
	xshmctl(shmid,IPC_RMID,NULL,__LINE__,__FILE__);
	return 0;	
}

bool primo(int n)
{
  int i;
  if(n<2) return false;
  if(n%2==0) {
    if(n==2)
      return true;
    else
      return false;
  }
  for (i=3; i*i<=n; i += 2) {
      if(n%i==0) {
          return false;
      }
  }
  return true;
}
