#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "tipi-moodle.h"



/* *************************************************************************************** */
/* Implementazione funzioni delle liste                                                  */
/* *************************************************************************************** */

Elemento *putElem(int value, char c)
{
    Elemento *e=(Elemento *)malloc(sizeof(Elemento));
    e->seed=c;
    e->value=value;
    return e;
}

bool emptyL(Lista l){
	return l == NULL;
}

void inserisci(Elemento el,Lista  *l){
	Lista l1=makeLista();
	l1 = (Nodo_lista *)malloc(sizeof(Nodo_lista));
	if (l1 != NULL) {
	  l1 ->inf = el;
	  l1 ->next = (*l);
       (*l) = l1;
}}

Elemento primo(Lista l){
	if (l != NULL)
	  return (l->inf);
}

Elemento rimuovi(Lista *lptr){
	if ((* lptr) != NULL) {
	    Elemento el=primo(*lptr);
	    Lista l = (* lptr);
	    (* lptr) = (* lptr)->next;
	    free(l);
	    return el;}
}

Lista makeLista(){
	return NULL;
}

/* *************************************************************************************** */
/* Implementazione funzioni delle pile                                                  */
/* *************************************************************************************** */

int emptyP(Pila p){
	return emptyL(p);
}

void push(Elemento el,Pila *p){
	inserisci(el, p);
}

Elemento *pop(Pila *p){
	return rimuovi(p);
}

Elemento *top(Pila p){
	return primo(p);
}

Pila makePila(){
	return makeLista();
}

/* *************************************************************************************** */
/* Implementazione funzioni delle code                                                  */
/* *************************************************************************************** */


int emptyC(Coda c){
	return emptyL(c.primo);
}

void enqueue(Elemento *el,Coda *c){
	Lista l=NULL;
	inserisci(el, &l);
	if(emptyC(*c))
	{
		(*c).primo = l;
		(*c).ultimo = l;

	} else {
		(*c).ultimo->next = l;
		(*c).ultimo = l;
	}
}

Elemento *dequeue(Coda *c){
	return rimuovi(&((*c).primo));
}

Elemento *first(Coda c){
	return primo(c.primo);
}

Coda makeCoda(){
	Coda c;
	c.primo =c.ultimo = NULL;
	return c;
}
