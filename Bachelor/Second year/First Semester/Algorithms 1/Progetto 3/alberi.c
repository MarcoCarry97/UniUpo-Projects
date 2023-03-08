#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<time.h>
#include"tree.h"

#define RUN 10

int main()
{
    srand(time(NULL));
    int n=10;
    //long *a=(long *)malloc(DIM*sizeof(long));
    long *a = NULL;
    while(n<=80)
    {
        tree t;
        t = initialize("studenti.txt",n,a);
        for(int i=0;i<RUN;i++)
        {
            int r=0;
            normalSearch(t,a[(int) rand()],&r);
            printf("Numero nodi visitati nella ricerca normale: %d\n",r);
            r=searchABR(t,a[(int) rand()]);
            printf("Numero nodi visitati nella ricerca ABR: %d\n",r);
        }
        n+=10;
    }
    return 1;
}
