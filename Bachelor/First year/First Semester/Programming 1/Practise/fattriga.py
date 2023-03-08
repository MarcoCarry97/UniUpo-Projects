#! /usr/bin/env python3


# esempio di programma pera il fattoriale eseguibile dalla linea di comando 

import sys

# solita funzione per il fattoriale
def fatt(n):
    f = 1
    for i in range(1,n+1):
        f *= i
    return f

# se gli argomenti sono 2 calcola e stampa il fattoriale
# altrimenti un messaggio d'errore
if len(sys.argv)==2:
    print(fatt(int(sys.argv[1])))
else:
      print("Uso:", sys.argv[0], "numero")
