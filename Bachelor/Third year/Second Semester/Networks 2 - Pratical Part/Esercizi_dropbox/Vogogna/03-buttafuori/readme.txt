@portNum compreso tra 10000 e 12000, altrimenti chiede nuovamente la porta

Lanciare il server con ./bouncerServerUDP @portNum
Lanciare il client con ./bouncerClientUDP @hostname @portNum

La prima volta che il client contatta il server, gli viene restituito
Received info:
	Protocol: http
	Hostname: www.cimiteromonumentalealessandria.it
	Port: 80
ottenuta dalla parsificazione della stringa ricevuta dal server http://www.cimiteromonumentalealessandria.it:80\n
Se entro 2 minuti il server viene contattato nuovamente dallo stesso client, ritorna
stop birching!
le prime 4 volte, e poi smette di rispondere fino al termine del cooldown
