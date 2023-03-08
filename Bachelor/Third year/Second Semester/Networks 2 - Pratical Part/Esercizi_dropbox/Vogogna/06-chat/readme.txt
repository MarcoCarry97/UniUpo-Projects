@portNum compreso tra 10000 e 12000, altrimenti chiede nuovamente la porta

Lanciare il server con ./echoServer @portNum
Lanciare un client con ./echoClient @hostname @portNum
Lanciare un altro client con ./echoClient @hostname @portNum

Inserire l'username per entrambi i clients.
Scambiarsi dei messaggi: vedo solo i messaggi in arrivo dagli altri, quelli che scrivo si leggono direttamente a video.
Ogni volta che un client si connette e decide un username, tutti i clients vengono notificati con la lista degli username dei client collegati.
(ricevendo una stringa dal server mentre se ne sta componendo una, il testo risulta difficilmente leggibile)
