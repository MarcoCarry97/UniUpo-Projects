/*Modifica Email Utente*/
update utente 
set Email = 'ab.it'
where Email = 'a.it'

/*Modifica Termini Sistemazione*/
update Sistemazione
set Termine = 'Flessibili'
where Nome = 'Z'

/*Modifica PrezzoPulizia Sistemazione*/
update Sistemazione
set PrezzoPulizia = 50
where Nome = 'Z'

/*Modifica Check_out prenotazione*/
update Prenotazione
set Check_out = '02-12-2018'
where id = 213

/*Modifica numero letti_letti di una sistemazione*/
update Contiene
set Numero_Letti = 3
where Sistemazione = 'D' and Tipo ='Singolo'

/*modifico il tipo di una risposta*/
update Risposte
set tipo = 'false'
where id = 149

/*Un proprietario diventa Superhost */
update Host
set Superhost = true
where Email = 'a.it'

/*Modifico il proprietario di una sistemazione
update Sistemazione
set Proprietario = 'b.it'
where Nome = 'Z'

