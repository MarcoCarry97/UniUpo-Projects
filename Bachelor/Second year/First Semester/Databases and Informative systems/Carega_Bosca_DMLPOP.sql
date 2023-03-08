insert into Lingua(Nome) values ('Italiano');
insert into Lingua(Nome) values ('Francese');
insert into Lingua(Nome) values ('Inglese');
insert into Lingua(Nome) values ('Tedesco');
insert into Lingua(Nome) values ('Portoghese');

insert into utente (Email,Data_nascita,Nome,Cognome) values('a.it','08-01-1995','Luca','Rossi');
insert into utente (Email,Data_nascita,Nome,Cognome) values('b.it','07-11-1998','Gianni','Roveta');
insert into utente (Email,Data_nascita,Nome,Cognome) values('c.it','15-07-1994','Matteo','Verdi');
insert into utente (Email,Data_nascita,Nome,Cognome) values('d.it','19-02-1999','Simone','Gialli');
insert into utente (Email,Data_nascita,Nome,Cognome) values('e.it','18-04-1975','Fiorenzo','Coda');
insert into utente (Email,Data_nascita,Nome,Cognome) values('f.it','20-12-1989','Daniele','Fiume');

insert into Parla(Utente,Lingua) values ('a.it','Inglese');
insert into Parla(Utente,Lingua) values ('b.it','Inglese');
insert into Parla(Utente,Lingua) values ('c.it','Francese');
insert into Parla(Utente,Lingua) values ('b.it','Italiano');
insert into Parla(Utente,Lingua) values ('d.it','Portoghese');
insert into Parla(Utente,Lingua) values ('c.it','Inglese');
insert into Parla(Utente,Lingua) values ('d.it','Tedesco');
insert into Parla(Utente,Lingua) values ('b.it','Francese');
insert into Parla(Utente,Lingua) values ('a.it','Portoghese');

insert into Termine(Nome) values ('Moderati');
insert into Termine(Nome) values ('Flessibili');
insert into Termine(Nome) values ('Rigidi');

insert into Tipologia(Nome) values ('Loft');
insert into Tipologia(Nome) values ('Condominio');
insert into Tipologia(Nome) values ('Villa');



insert into Host(Email,Numero_proprietà,Superhost) values ('a.it',1,'false');
insert into Host(Email,Numero_proprietà,Superhost) values ('b.it',2,'true');
insert into Host(Email,Numero_proprietà,Superhost) values ('f.it',1,'true');

insert into Sistemazione(Nome,Proprietario,luogo,descrizione,termine,Tipo_Sistemazione,Tipologia, Cauzione, PrezzoExtra, PrezzoPulizia, NumeroBagni, NumeroCamere,PostiLetto, Appartamento)
values ('Z','a.it','L','y','Rigidi','true','Loft',10,15,20,2,4,1,null);
insert into Sistemazione(Nome,Proprietario,luogo,descrizione,termine,Tipo_Sistemazione,Tipologia, Cauzione, PrezzoExtra, PrezzoPulizia, NumeroBagni, NumeroCamere,PostiLetto, Appartamento)
values ('D','b.it','L','y','Moderati','true','Loft',10,16,30,1,4,7,null);
insert into Sistemazione(Nome,Proprietario,luogo,descrizione,termine,Tipo_Sistemazione,Tipologia, Cauzione, PrezzoExtra, PrezzoPulizia, NumeroBagni, NumeroCamere,PostiLetto, Appartamento)
values ('E','b.it','L','y','Moderati','true','Loft',11,18,30,1,2,7,null);
insert into Sistemazione(Nome,Proprietario,luogo,descrizione,termine,Tipo_Sistemazione,Tipologia, Cauzione, PrezzoExtra, PrezzoPulizia, NumeroBagni, NumeroCamere,PostiLetto, Appartamento)
values ('G','f.it','O','y','Flessibili','false','Condominio',10,12,30,2,3,7,'E');

insert into Servizio(Nome) values('Parcheggio');
insert into Servizio(Nome) values('Ascensore');
insert into Servizio(Nome) values('Parco');
insert into Servizio(Nome) values('Sala');

insert into TipoLetto(Nome,Numero_posti) values('Singolo',1);
insert into TipoLetto(Nome,Numero_posti) values('Matrimoniale',2);

insert into Contiene values('D','Singolo',2);
insert into Contiene values('D','Matrimoniale',1);
insert into Contiene values('Z','Singolo',1);
insert into Contiene values('E','Matrimoniale',2);
insert into Contiene values('G','Matrimoniale',1);

insert into offerta values('Sala','D');
insert into offerta values('Sala','Z');
insert into offerta values('Parcheggio','D');
insert into offerta values('Ascensore','D');

insert into prenotazione values(123,'a.it','D','01-01-2001','01-03-2001','true');
insert into prenotazione values(321,'a.it','Z','02-05-2018','01-08-2018','false');
insert into prenotazione values(213,'b.it','E','06-05-2018','11-09-2018','false');
insert into prenotazione values(234,'f.it','D','05-11-2011','01-05-2012','true');
insert into prenotazione values(432,'c.it','G','05-05-2013','01-06-2013','true');
insert into prenotazione values(435,'c.it','D','25-07-2017','01-09-2017','true');

insert into  Recensioni_Sistemazioni values(222,'E','Tutto ok',5,2);
insert into  Recensioni_Sistemazioni values(111,'D','Tutto di mio gradimento',5,1);
insert into  Recensioni_Sistemazioni values(123,'Z','Qualche problema',3,0);
insert into  Recensioni_Sistemazioni values(134,'D','Sono contento',4,0);
insert into  Recensioni_Sistemazioni values(121,'D','I servizi possono essere migliorati',2,2);
insert into  Recensioni_Sistemazioni values(245,'G','Tutto ok,miglioriamo',4,1);

insert into Recensioni_Utenti values(211,'a.it','utente gradito',5);
insert into Recensioni_Utenti values(231,'b.it','utente un po maleducato',2);
insert into Recensioni_Utenti values(331,'c.it','utente accetabile',3);
insert into Recensioni_Utenti values(531,'a.it','utente molto rispettoso',5);
insert into Recensioni_Utenti values(541,'f.it','utente molto gradito',5);

insert into Risposte values(145,222,'Grazie per la buona recensione',false);
insert into Risposte values(146,245,'Sono contento',true);
insert into Risposte values(147,121,'Posso pensarci',false);
insert into Risposte values(148,121,'Giusto!',false);
insert into Risposte values(149,111,'Grazie per la buona recensione,sono felice',true);
insert into Risposte values(150,222,'La ringrazio',false);