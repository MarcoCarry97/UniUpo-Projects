#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"tipi-moodle.h"

#define CARDS 40
#define PLAY 4

void insertCards(char seed, Coda *q);
void shuffle(Coda *q);
void putOnTable(Coda *q,Lista *l);
void giveToPlayers(Coda *q,Pila p[PLAY]);

int main()
{
    //DICHIARAZIONE E INIZIALIZZAZIONE
    Pila player[PLAY];
    for(int i=0;i<PLAY;i++) player[i]=makePila();
    Lista table= makeLista();
    Coda deck=makeCoda();
    insertCards('C',&deck);
    insertCards('Q',&deck);
    insertCards('F',&deck);
    insertCards('P',&deck);
    //PRIMA MANO
    int cnt=1;
    //while(cnt<=CARDS) shuffle(&deck);
    putOnTable(&deck,&table);
    giveToPlayers(&deck,player);
}

void insertCards(char seed, Coda *q)
{
    for(int i=1;i<=10;i++)
    {
        Elemento *d=putElem(i,seed);
        enqueue(d,q);
    }
}

void shuffle(Coda *q)
{
    int x= 1 +rand()%(CARDS-1), y= 1 +rand()%(CARDS-1);
    int cnt=2,pos=1;
    Lista l=q->primo;
    Elemento *e, *f;
    while(cnt!=0)
    {
        if(pos==x)
        {
            cnt--;
            e=q->inf;
        }
        else if(pos==y)
        {
            cnt--;
            f=l->inf;
        }
        l=l->next;
        pos++;
    }
}

void putOnTable(Coda *q, Lista *l)
{
    Lista n=(*l), tail=NULL;
    for(int i=0;i<4;i++)
    {
        while(n!=NULL)
        {
            Lista p=(Elemento *)malloc(sizeof(Elemento));
            p->(*d)=dequeue(q);
            p->next=NULL;
            if((*l)==NULL) (*l)=p;
            else tail->next=p;
            tail=p;
        }
        n=(*l);
    }
}

void giveToPlayers(Coda *q,Pila p[4])
{
    for(int i=0;i<3;i++)
        push(dequeue(q),p[i]);
}
