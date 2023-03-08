#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

void continua()
{
	int scelta;
	do
	{
		printf("sei un coglione\n");
		printf("puoi dare la colpa a qualcun'altro?\n");
		scanf("%d",&scelta);
	}
	while(!scelta);
}

int main()
{
	printf("NOTA: scrivere 1 per il Si e 0 per il No.\n.\n.\n.\n");
	printf("PROBLEMA DI LAVORO\n");
	int scelta;
	bool fine=false;
	printf("E' di tua competenza?\n");
	scanf("%d",&scelta);
	if(scelta)
	{
		printf("ti possono inculare?\n");
		scanf("%d",&scelta);
		if(scelta)
		{
			printf("puoi passarlo ad altri?\n");
			scanf("%d",&scelta);
			if(scelta)
			{
				printf("e' tornato su di te?\n");
				scanf("%d",&scelta);
				if(scelta) continua();
			}
			else
			{
				printf("lo sai risolvere?\n");
				scanf("%d",&scelta);
				if(!scelta) continua();
				else
				{
					printf("qualcuno ne é a conoscenza?\n");
					scanf("%d",&scelta);
					if(scelta) continua();
					else printf("non parlarne con nessuno\n");
				}
			}
		}
	}
	else printf("che s'inculino\n");
	printf("IL PROBLEMA E' RISOLTO\n");
	return 0;
}
