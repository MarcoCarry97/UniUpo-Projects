#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

typedef struct person
{
	char nome[20];
	char cogn[25];
	int eta;
}person;

person *riempi(int dim)
{
	person *vet=(person *)malloc(dim*sizeof(person));
	for(int i=0;i<dim;i++)
	{
		printf("inserire nome\n");
		scanf("%s",vet[i].nome);
		printf("inserire cognome\n");
		scanf("%s",vet[i].cogn);
		printf("inserire eta'\n");
		scanf("%d",&vet[i].eta);
	}
	return vet;
}

void stampa(person vet[], int i)
{
	printf("%s ",vet[i].nome);
	printf("%s ",vet[i].cogn);
	printf("%d\n",vet[i].eta);
}

void stampatutto(person vet[], int num)
{
	//printf("sono dentro\n");
	for(int i=0;i<num;i++)
	{
		//printf("nel for\n");
		stampa(vet,i);
	}
}

void transfer(person emit[],int em,person dest[],int de)
{
	strncpy(dest[de].nome,emit[em].nome,20);
	strncpy(dest[de].cogn,emit[em].cogn,25);
	dest[de].eta=emit[em].eta;
}

void dividi(person vet[],int num,person over[],int *mag,person under[],int *min)
{
	//over=(person *)malloc(num*sizeof(person));
	//under=(person *)malloc(num*sizeof(person));
	int contamag=0,contamin=0;
	for(int i=0;i<num;i++)
	{
		if(vet[i].eta>=18)
			transfer(vet,i,over,contamag++);
		else
			transfer(vet,i,under,contamin++);
	//	printf("%5s\n",over[contamag-1].nome);
	//	printf("%5s\n",under[contamin-1].nome);
	}
	over=(person *)realloc(over,contamag*sizeof(person));
	under=(person *)realloc(under,contamin*sizeof(person));
	*mag=contamag;
	*min=contamin;
}

int main()
{
	int dim;
	printf("inserire grandezza\n");
	scanf("%d",&dim);
	person *vet=riempi(dim);
	person *magg=(person *)malloc(dim*sizeof(person));
	person *minn=(person *)malloc(dim*sizeof(person));
	int cmag=0,cmin=0;
	dividi(vet,dim,magg,&cmag,minn,&cmin);
	//printf("%s ",vet[1].nome);
	printf("MAGGIORENNI\n");
	printf("%d %d\n",cmag,cmin);
	stampatutto(magg,cmag);
	//stampatutto(vet,dim);
	printf("MINORENNI\n");
	stampatutto(minn,cmin);
	return 0;
}
