#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<sys/types.h>

#include"xerrors.h"

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("Uso: %s numProcess fileName\n",argv[0]);
		exit(0);
	}
	int numProcess=atoi(argv[1]);
	int down[2], up[2];
	xpipe(down,__LINE__,__FILE__);
	xpipe(up,__LINE__,__FILE__);
	pid_t pid;
	for(int i=0;i<numProcess;i++)
	{
		pid=xfork(__LINE__,__FILE__);
		if(pid==0)
		{
			int sum=0, num=0;
			bool end=false;
			while(!end)
			{
				close(down[1]);
				int e=read(down[0],&num,sizeof(int));
				assert(e!=-1);
				//printf("il processo %d legge %d, stato:%d\n",getpid(),num,e);
				if(e==0) end=true;
				else sum+=num;
			}
			//printf("somma del processo %d: %d\n",getpid(),sum);
			close(down[0]);
			close(up[0]);
			int e=write(up[1],&sum,sizeof(int));
			assert(e==sizeof(int));
			close(up[1]);
			exit(0);
		}
	}
	FILE *in=xfopen(argv[2],"r",__LINE__,__FILE__);
	bool end=false;
	while(!end)
	{
		int num=-1;
		fscanf(in,"%d",&num);
		//printf("num: %d\n",num);
		if(feof(in)) end=true;
		else
		{
			close(down[0]);
			int e=write(down[1],&num,sizeof(int));
			assert(e!=-1);
		}
	}
	fclose(in);
	close(down[1]);
	int sum[numProcess];
	for(int i=0;i<numProcess;i++) pid=xwait(NULL,__LINE__,__FILE__);
	for(int i=0;i<numProcess;i++)
	{		
		close(up[1]);
		int e=read(up[0],&sum[i],sizeof(int));
		assert(e!=-1);
	}
	close(up[0]);
	int tot=0;
	//for(int i=0;i<numProcess;i++) printf("sum: %d\n",sum[i]);
	for(int i=0;i<numProcess;i++) tot+=sum[i];
	printf("somma di %s con %d processi: %d\n",argv[2],numProcess,tot);
	return 0;
}
