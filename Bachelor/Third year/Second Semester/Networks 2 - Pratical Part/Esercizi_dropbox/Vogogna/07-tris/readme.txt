@portNum compreso tra 10000 e 12000, altrimenti chiede nuovamente la porta

Lanciare il server con ./server @portNum
Lanciare un client con ./client @hostname @portNum
Lanciare un altro client con ./client @hostname @portNum

Il server rimane in attesa fino a quando non si collegano un numero pari di clients (può gestire più partire in contemporanea).
Una volta creata la partita assegna in modo casuale il turno ad uno dei due giocatori.
Per giocare una mossa, bisogna inserire
	'posizione vertical'-'posizione orizzontale'
ad esempio 0-2, 1-0, ecc.
Se si inseriscono valori al di fuori della matrice, viene restituito un errore e tocca sempre allo stesso giocatore.
Stessa cosa se si cerca di fare una mossa in una posizione già occupata.
Non si può fare nulla nel turno dell'avversario.
Se un client chiude la connessione, il suo avversario vince automaticamente per ritiro.
