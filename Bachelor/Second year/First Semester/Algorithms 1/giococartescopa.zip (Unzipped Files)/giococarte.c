#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"structure.h"


#define CARDS 40
#define PLAY 4
#define SEED 4

void insertCards(char *seed, queue *q);
void shuffle(queue *q);
void putOnTable(queue *q,list *l);
void giveToPlayers(queue *q,stack p[]);
void swap(data *a, data *b);
void rejectCards(stack *p,list *l);

int main()
{
	//DICHIARAZIONE E INIZIALIZZAZIONE
	int scelta;
	stack player[PLAY];
	for(int i=0;i<PLAY;i++){
        makeStack(&player[i]);
    }
    puts("->Giocatori creati");
	list table;
	makeList(&table);
	puts("->tavolo creato");
	queue deck;
	makeQueue(&deck);
	puts("->mazzo creato");
	char seed[SEED];
    seed[0] = 'C';
    seed[1] = 'F';
    seed[2] = 'P';
    seed[3] = 'Q';
	insertCards(seed,&deck);
	puts("->carte inserite");
	//PRIMA MANO
	shuffle(&deck);
	puts("->carte mischiate");
	putOnTable(&deck,&table);
	puts("->carte sul tavolo");
    printf("Vuoi visualizare le carte sul tavolo? 0/1\n");
    scanf("%d", &scelta);
    if(scelta==1){
        puts("Situazione tavolo:");
        printList(table);
        puts("***");
    }
	giveToPlayers(&deck,player);
	puts("->carte ai giocatori\n");
	//ALTRE MANI
	while(!isEmptyQueue(deck))
	{
        printf("Vuoi visualizare le carte in mano ad ogni giocatore? 0/1\n");
        scanf("%d", &scelta);
        if(scelta==1){
            for(int k=0; k<PLAY; k++){
                printf("Carte in mano al giocatore %d:\n", k);
                printList(player[k]);
                puts("---");
            }
        }
        puts("***");
		for(int i=0;i<PLAY;i++){
            while(!isEmptyStack(player[i])){
                rejectCards(&player[i],&table);
                printf("Vuoi visualizare la carta giocata dal giocatore %d? 0/1\n", i);
                scanf("%d", &scelta);
                if(scelta==1){
                    printf("carta: %d%s\n", table->d.value, &table->d.seed);
                }
                printf("Vuoi visualizare la situazione del gioco? 0/1\n");
                scanf("%d", &scelta);
                if(scelta==1){
                    puts("#SITUAZIONE DEL GIOCO#");
                    puts("**Tavolo:**");
                    printList(table);
                    puts("**Carte in mano ai giocatori:**");
                    for(int k=0; k<PLAY; k++){
                        printf("Carte in mano al giocatore %d:\n", k);
                        printList(player[k]);
                    }
                    puts("**Mazzo:**");
                    printList(deck.first);
                }
            }
        }
        puts("***");
        //puts("carte in campo\n");
		giveToPlayers(&deck,player);
		puts("->carte ai giocatori");

    }
		//puts("carte ai giocatori\n");
	puts("->Il mazzo è vuoto<-");
	return 1;
}

void insertCards(char *seed, queue *q)
{
	for(int i=0;i<SEED;i++){
        //printf("%s\n", &seed[i]);
		for(int j=1;j<=10;j++){
            //printf("%d\n", j);
            data d =putData(j, seed[i]);
            //printf("dato: %s, %d\n", &d.seed, d.value);
			enQueue(q,d);
        }
    }
}

void shuffle(queue *q)
{
	int tot=1;
	while(tot<=40)
	{
		int cnt=2;
		int pos=1;
		int x=rand()%(CARDS),y=rand()%(CARDS);
		data *a=NULL, *b=NULL;
		list l=q->first;
		while(cnt>0)
		{
			if(pos==x)
			{
				cnt--;
				a=&(l->d);
			}
			else if(pos==y)
			{
				cnt--;
				b=&(l->d);
			}
			l=l->next;
			pos++;
		}
		//printf("Scambio = %d%s con %d%s\n", a->value, &a->seed, b->value, &b->seed);
		swap(a,b);
		//puts("scambiati\n");
		tot++;
	}
}

void swap(data *a,data *b)
{
	data tmp;
	copyData(&tmp, (*a));
	copyData(a, (*b));
	copyData(b, tmp);
}

void putOnTable(queue *q,list *l)
{
	for(int i=0;i<4;i++){
        data d = deQueue(q);
		inserisci(d,l);
    }
}

void giveToPlayers(queue *q,stack p[])
{
	for(int i=0;i<3;i++)
		for(int j=0;j<PLAY;j++)
			push(&p[j],deQueue(q));
}

void rejectCards(stack *p, list *l)
{
        data d = pop(p);
        inserisci(d,l);
}
