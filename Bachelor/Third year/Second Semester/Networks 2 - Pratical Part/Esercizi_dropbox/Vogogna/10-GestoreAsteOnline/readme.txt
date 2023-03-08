Ho utilizzato le API mysql per gestire utenti, oggetti e scommesse. Bisogna quindi aver installato mysql-server e libmysqlclient-dev.
Inserire indirizzo IP, username e password da utilizzare su mysql all'interno del file mysql.h, nella parte indicata. (di default viene utilizzato il database con nome la mia matricola 10035843 e password uguale)
All'avvio del directory server verr� creata la tabella users (se non esisteva gi�).
All'avvio di un qualsiasi server, verranno create tabelle items e bids (se non esistevano gi�).

@portNum compreso tra 10000 e 12000, altrimenti chiede nuovamente la porta

Lanciare il directory server con ./directory_server @portNum
Lanciare uno o pi� server con ./server @directory_server_address @directory_server_port @portNum
Lanciare un client con ./client @directory_server_address @directory_server_port

Directory server e client sono implementati con la select, sanno quindi se un client o un server (directory o non), rispettivamente, sono stati uccisi.
Il server � implementato usando la fork, assegnando un nuovo processo figlio ad ogni client che si collega.
Nel caso un server che stava gestendo un client muoia, il client chiede l'indirizzo di un server connesso al directory server e vi si ricollega. Se non vi sono server attivi entro 15 secondi (il client fa tra 3 tentativi, uno ogni 5 secondi), il client esce chiedendo di riprovare pi� tardi.
Alla riconnessione del client al server, si ricomincer� dal men� principale.

Bisogna registrare un utente per poter vendere un oggetto o fare offerte (inserendo username desiderato, password e nuovamente la password. Non � possibile creare utenti con un username gi� presente nel database).
Il venditore di un oggetto non pu� fare offerte sui suoi oggetti in vendita.
Se un utente sta gi� vincendo un oggetto, non pu� aumentare la sua offerta.
Agli oggetti messi in vendita si pu� solo assegnare un nome, mentre durata dell'asta e prezzo di partenza sono impostati di default a 3 giorni e 1 credito rispettivamente.

Ho aggiunto un listato degli ultimi 10 oggetti messi in vendita ed una ricerca degli oggetti per nome. In pi� � possibile vedere gli oggetti che si stanno attualmente vendendo, gli oggetti vinti, e gli oggetti su cui si sono fatte offerte.
Per fare un'offerta bisogna cercare un oggetto, o per nome, o nel listato degli oggetti in scadenza, inserire l'id dell'oggetto su cui si vuole puntare, e, in un secondo momento, inserire la puntata (le richieste vengono fatte direttamente dal server).
