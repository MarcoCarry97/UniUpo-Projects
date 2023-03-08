@portNum compreso tra 10000 e 12000, altrimenti chiede nuovamente la porta

Lanciare il server con ./searchServer @portNum
Lanciare il client con ./searchClient @hostname @portNum

Inserire la stringa da ricercare ed il nome del file in cui cercarla nel formato
	stringa-nomefile.estensione

Il risultato restituito può essere:
	String "stringa" found at line lineNum
	String "stringa" wasn't find in the file
	File "nomefile.estensione" doesn't exist
	Message in the wrong format
	