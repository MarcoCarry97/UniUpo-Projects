#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

typedef struct person
{
	char nome[20];
	char cogn[20];
	int eta;
}DATA;

DATA copia(DATA d)
{
	DATA p;
	strcpy(p.nome,d.nome);
	strcpy(p.cogn,d.cogn);
	p.eta=d.eta;
	return p;
}

void stampadato(DATA d)
{
	printf("%s %s %d\n",d.nome,d.cogn,d.eta);
}

void riempi(DATA vet[], int num,char nome[],FILE *f,int c, bool open)
{
	if(c==EOF) fclose(f);
	else
	{
		if(!open)
		{
			f=fopen(nome,"r");
			riempi(vet,num,nome,f,c,true);
		}
		else
		{
			c=fscanf(f,"%s %s %d",vet[num].nome,vet[num].cogn,&vet[num].eta);
			riempi(vet,num-1,nome,f,c,open);
		}
	}
}

void stampavet(DATA vet[], int num)
{
	if(num>=0)
	{
		stampavet(vet,num-1);
		stampadato(vet[num]);
	}
}

void etamaxmin(DATA vet[], int num,int *max,int *min)
{
	if(num>0)
	{
		if((*max)<vet[num].eta) (*max)=vet[num].eta;
		if((*min)>vet[num].eta) (*min)=vet[num].eta;
		etamaxmin(vet,num-1,max,min);
	}
}

void persmaxmin(DATA vet[],int num,DATA *pmax,DATA *pmin)
{
	if(num>0)
	{
		if(vet[num].eta>pmax->eta) (*pmax)=copia(vet[num]);
		if(vet[num].eta>pmin->eta) (*pmin)=copia(vet[num]);
		persmaxmin(vet,num-1,pmax,pmin);
	}
}

int sommag(DATA vet[], int num)
{
	if(num<0) return 0;
	else if(vet[num].eta>=18) return vet[num].eta + sommag(vet,num-1);
	else return sommag(vet, num -1);
}

bool palindromo(char stri[], int num, int pos)
{
	if(num==0 || num==1) return true;
	else if(stri[pos]==stri[num]) return palindromo(stri,pos+1,num -1);
	else return false;
}

void vetpalin(DATA vet[],int num)
{
	if(num>=0)
	{
		if(palindromo(vet[num].nome,strlen(vet[num].nome),0)) printf("%s\n",vet[num].nome);
		vetpalin(vet,num-1);
	}
}

int main()
{
	int num;
	printf("inserire numero");
	scanf("%d",&num);
	DATA vet[num];
	FILE *f;
	riempi(vet,num,"persone.txt",f,0,false);
	int max=vet[0].eta,min=vet[0].eta;
	etamaxmin(vet,num,&max,&min);
	DATA pmax=copia(vet[0]), pmin=copia(vet[0]);
	persmaxmin(vet,num,&pmax,&pmin);
	stampadato(pmax);
	stampadato(pmin);
	int sommaeta=sommag(vet,num);
	printf("SOMMA MAGGIORENNI:%d\n",sommaeta);
	vetpalin(vet,num);
	return 0;
}
