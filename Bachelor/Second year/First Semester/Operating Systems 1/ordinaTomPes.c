#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include "xerrors.h"


// genera array di n elementi con interi random tra 0 e RAND_MAX
int *random_array(int n)
{
  assert(n>0);
  int *a = malloc(n* sizeof(int));
  assert(a!=NULL);
  for(int i=0;i < n;i++)
    a[i] = (int) random();
  return a;
}


// funzione di confronto tra interi passata da array_sort a qsort
int intcmp(const void *a, const void *b)
{
  return *((int *) a) - *((int *) b);
}
// esegue il sort dell'array a[0..n] utilizzando la funzione di libreria qsort
void array_sort(int *a, int n)
{
  qsort(a,n,sizeof(int), intcmp);
}

// verifica che array a[0..n] sia ordinato
bool check_sort(int *a, int n)
{
  for(int i=0;i<n-1; i++)
    if(a[i] > a[i+1]) return false;
  return true;
}

/*int unisci(int *arr1, int *arr2, int cont1, int cont2){
    int i=0;
    while()
}*/

int main(int argc, char *argv[])
{
  // leggi input
  if(argc!=2) {
    printf("Uso\n\t%s quantità da ordinare\n", argv[0]);
    exit(1);
  }
  int n = atoi(argv[1]);
  int *arr = (int *) malloc(n*sizeof(int));
  assert(arr!=NULL);
  arr = random_array(n);
  int i,e,c1,c2;
  c1=0;
  c2=0;
  //bool flag;
  pid_t pid;
  //Divide array
  int *arr1 = (int *) malloc(n*sizeof(int));
  int *arr2 = (int *) malloc(n*sizeof(int));
  for(i=0; i<n; i++){
    if(arr[i] < (RAND_MAX/2)){
        arr1[c1] = arr[i];
        c1++;
    }
    else{
        arr2[c2] = arr[i];
        c2++;
    }
  }
  // crea pipe per la comnicazione dai figli al padre.
  int up[2];
  xpipe(up,__LINE__,__FILE__);
  // crea i processi assegnandogli intervalli distinti
  pid = xfork(__LINE__,__FILE__);
  if (pid==0) {
    // codice dei processi figli
    fprintf(stderr,"Figlio con pid %d cerca fino a %d\n",getpid(), RAND_MAX);
    array_sort(arr2, c2);
    //flag = check_sort(arr2, c2);
    close(up[0]);
    e  = write(up[1],arr2,c2*sizeof(int));
    assert(e==c2*sizeof(int));
    close(up[1]);
    exit(0);
  }
  array_sort(arr1, c1);
  close(up[1]);
  e = read(up[0],arr2,c2*sizeof(int));
  if(e!=c2*sizeof(int)) {perror("Errore lettura pipe"); exit(1);}
  printf("Array1:\n");
  //Stampe dei due array
  for(int k=0; k<c1; k++){
    printf("Elemento %d: %d\n",k,arr1[k]);
  }
  printf("Array2:\n");
  for(int j=0; j<c2; j++){
    printf("Elemento %d: %d\n",j,arr2[j]);
  }
  //Unione array
  int *arrord = (int *) malloc(n*sizeof(int));
  int conta = 0;
  for(int w=0; w<c1; w++){
    arrord[conta] = arr1[w];
    conta++;
  }
  for(int z=0; z<c2; z++){
    arrord[conta] = arr2[z];
    conta++;
  }
  if(check_sort(arrord,n)==true) printf("--Array di partenza ordinato--\n");
  else printf("!!Array di partenza NON ordinato!!\n");
  printf("Array di partenza risultante:\n");
  for(int p=0; p<n; p++){
    printf("Elemento %d: %d\n",p,arrord[p]);
  }


}
