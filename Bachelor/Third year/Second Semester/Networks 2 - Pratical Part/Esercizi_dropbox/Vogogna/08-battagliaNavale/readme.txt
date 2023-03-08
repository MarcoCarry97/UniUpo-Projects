@portNum compreso tra 10000 e 12000, altrimenti chiede nuovamente la porta

Lanciare il server con ./server @portNum
Lanciare un client con ./client @hostname @portNum
Lanciare un altro client con ./client @hostname @portNum

Il server rimane in attesa fino a quando non si collegano un numero pari di clients (può gestire più partire in contemporanea).
Per prima cosa bisogna posizionare le navi (per comodità si gioca con solo 2 navi, 1 submarine ed 1 corvette, ma possono essere ripristinate
impostando NUMSHIPS (my_functions.h) al numero totale di caselle occupate dalle navi ed impostare il numero di ogni nave con NUM@nave (sempre in my_functions.h).
Per posizionare le navi si usa la sintassi
	nave x-y direzione
dove nave:(b=battleship,c=corvette,s=submarine,l=lance),
     x una lettera compresa tra a e j
     y un numero compreso tra 1 e 10
     direzione:(0=orizzontale,1=verticale)
Quando entrambi i giocatori hanno inserito le navi inizia la partita.
Il server assegna in modo casuale il turno ad uno dei due giocatori.
Per giocare una mossa, bisogna inserire
	'riga'-'colonna'
ad esempio g-2, a-0, j-8, ecc.
Se si inseriscono valori al di fuori della matrice, viene restituito un errore e tocca sempre allo stesso giocatore.
Stessa cosa se si cerca di fare una mossa in una posizione già occupata.
Non si può fare nulla nel turno dell'avversario.
Se un client chiude la connessione, il suo avversario vince automaticamente per ritiro.
