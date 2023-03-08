#include<stdio.h> //librerie
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct DATA //struct dell'esame
{
	char cognome[20];
	char nome[20];
	int matricola;
	char esame[20];
	int crediti;
	int voto;
}DATA;

typedef struct linked //struct della lista
{
	DATA d;
	struct linked *next;
}ELEMENT;
typedef ELEMENT *LINK;

LINK newnode()
{
	return (ELEMENT *)malloc(sizeof(ELEMENT));
}

int getdata(FILE *f, DATA *d) //prende una riga del file di testo alla volta
{
	fscanf(f,"%s",d->cognome);
	fscanf(f,"%s",d->nome);
	fscanf(f,"%d",&d->matricola);
	fscanf(f,"%s",d->esame);
	fscanf(f,"%d",&d->crediti);
	int end=fscanf(f,"%d",&d->voto);
	return end;
}

void copynode(LINK *p,DATA d) //copia la riga presa precedentemente nel nodo
{
	strcpy((*p)->d.cognome,d.cognome);
	strcpy((*p)->d.nome,d.nome);
	(*p)->d.matricola=d.matricola;
	strcpy((*p)->d.esame,d.esame);
	(*p)->d.crediti=d.crediti;
	(*p)->d.voto=d.voto;
	(*p)->next=NULL;
}

void aggiungi(LINK *head,LINK *tail,LINK p) //aggiunge un nodo alla lista
{
	if((*head)==NULL) (*head)=p; //se la lista é vuota, inserisco il nodo in testa alla lista
	else (*tail)->next=p; //altrimenti lo inserisco in coda
	(*tail)=p;
}

LINK readfile(char nome[]) //PUNTO 1
{
	LINK head=NULL, tail=NULL;
	FILE *f=fopen(nome,"r"); //apro il file in lettura.
	if(f==NULL) //controllo se il file esiste o meno.
	{
		printf("file non trovato\n");
		return NULL; //IL FILE NON ESISTE
	}
	DATA node; //IL FILE ESISTE
	int end=getdata(f,&node);
	while(end!=EOF) //controllo se il file é finito o meno (EOF é una costante che vale -1 che indica la fine di un file di testo).
	{//quando il file é finito, la funzione fscanf() restituirà -1 (la inserirà dentro la variabile end), in questo modo si uscirà dal ciclo e il programma passerà alla riga successiva.
		LINK p=newnode(); //creo un nodo.
		copynode(&p,node); //inserisco i dati nel nodo.
		aggiungi(&head,&tail,p);
		end=getdata(f,&node); //passo alla riga successiva del file
	}
	fclose(f);
	return head;
}

void printdata(DATA d) //stampa un nodo della lista
{
	printf("%s ",d.cognome);
	printf("%s ",d.nome);
	printf("%d ",d.matricola);
	printf("%s ",d.esame);
	printf("%d ",d.crediti);
	printf("%d\n",d.voto);
}

void printlis(LINK lis) //PUNTO 2
{
	if(lis!=NULL) //CASO INTERMEDIO
	{
		printdata(lis->d); //stampo il nodo
		printlis(lis->next); //passo al nodo successivo
	}
}

int matcrediti(LINK lis, int mat) //PUNTO 3
{
	if(lis==NULL) return 0; //CASO BASE: esco dalla ricorsione
	else if(lis->d.matricola!=mat) return matcrediti(lis->next,mat); //CASO INTERMEDIO 1: passo al nodo successivo
	else return lis->d.crediti + matcrediti(lis->next,mat); //CASO INTERMEDIO 2: sommo e passo al nodo successivo
}
	
LINK solocogn(LINK *lis,char cogn[]) //PUNTO 4
{
	LINK q=(*lis); //dato che ho passato la lista per riferimento, utilizzo una variabile LINK per mantenere la testa della lista
	LINK head=NULL, tail=NULL,newtail=NULL,p;
	(*lis)=NULL;
	while(q!=NULL)
	{
		p=q;
		q=q->next;
		p->next=NULL;
		if(!strcmp(p->d.cognome,cogn)) aggiungi(&head,&tail,p);
		else aggiungi(lis,&newtail,p);
	}
	return head;	
}	
	
int main()
{
	LINK l1=readfile("input-esame.txt"); //PUNTO 1: creo una lista contenente i dati all'interno del file di testo.
	printlis(l1); //PUNTO 2: stampa a video i nodi di una lista.
	int mat, sommacrediti;
	printf("inserire matricola per sommare i suoi crediti\n");
	scanf("%d",&mat);
	sommacrediti=matcrediti(l1,mat); //PUNTO 3: data una matricola, restituisco la somma dei suoi crediti.
	printf("crediti di %d: %d\n",mat,sommacrediti);
	char cogn[20];
	printf("inserire cognome per creazione lista\n");
	scanf("%s",cogn);
	LINK l2=solocogn(&l1,cogn); //PUNTO 4: creo una nuova lista contenente i nodi che hanno il cognome dato come parametro, ELIMINANDOLI DA QUELLA ORIGINALE.
	printlis(l2);
	printf("prima lista modificata\n");
	printlis(l1);
	return 0;
}
