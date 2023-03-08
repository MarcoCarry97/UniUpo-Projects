typedef struct elemento
{
    int value;
    char seed;
}Elemento;

/* *************************************************************************************** */
/* Definizione del tipo lista i cui elementi sono di tipo Elemento (per il momento int)
 * con le operazioni di inserzione in testa, estrazione dalla testa,  accesso all'emento
 * in testa (primo),  costruzione della lista vuota (makeLista) e test se vuota (emptyL)     */
/* *************************************************************************************** */


typedef struct Nodo_lista {
    Elemento inf;
    struct Nodo_lista *next;
} Lista;

//typedef struct Nodo_lista *Lista ;

int emptyL(Lista *l);
void inserisci(Elemento el,Lista *l);
Elemento rimuovi(Lista *l);
Elemento primo(Lista *l);
Lista makeLista();

/* *************************************************************************************** */
/* Definizione del tipo Pila con le operazioni pop push top test se vuota (emptyP) e
 * costruzione della pila vuota (makePila) implementato con una lista                      */
/* *************************************************************************************** */

typedef Lista Pila;

int emptyP(Pila);
void push(Elemento el,Pila*);
Elemento pop(Pila*);
Elemento top(Pila);
Pila makePila();

/* *************************************************************************************** */
/* Definizione del tipo Coda con le operazioni enqueue dequeue first test se vuota (emptyC)
 * costruzione dalla coda vuota (makeCoda) implementato con una struttura contenente
 * una lista (cont) e puntatori al primo e ultimo elemento  (primo, ultimo)                  */
/* *************************************************************************************** */

struct coda {
	Lista primo;
	Lista ultimo;
} coda;

typedef struct coda Coda ;

int emptyC(Coda);

void enqueue(Elemento el,Coda*);

Elemento dequeue(Coda*);

Elemento first(Coda);

Coda makeCoda();
