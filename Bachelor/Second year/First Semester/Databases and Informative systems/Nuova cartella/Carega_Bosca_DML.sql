create table Termine(
	Nome varchar(20),
	primary key(Nome)
);

create table Tipologia(
	Nome varchar(20),
	primary key(Nome)
);

create table TipoLetto(
	Nome varchar(20),
	Numero_posti smallint,
	primary key (Nome)
);

create table Servizio(
	Nome varchar(30),
	primary key(Nome)
);

create table Utente(
	Email varchar(30),
	Data_nascita date,
	Nome varchar(20),
	Cognome varchar(20),
	primary key(Email)
);

create table Host(
	Email varchar(30),
	Numero_proprietà smallint,
	SuperHost boolean,
	primary key(Email),
	constraint fk_host foreign key (Email) references Utente(Email)
		on update cascade
		on delete cascade
);



create table Sistemazione(
	Nome varchar(30),
	Proprietario varchar(30),
	Luogo varchar(30),
	Descrizione varchar(200),
	Termine varchar(20),
	Tipo_Sistemazione boolean,
	Tipologia varchar(20),
	Cauzione integer,
	PrezzoExtra integer,
	PrezzoPulizia integer,
	NumeroCamere integer,
	NumeroBagni integer,
	PostiLetto smallint,
	Appartamento varchar(30) default NULL,
	primary key (Nome),
	constraint fk_Term foreign key(Termine) references Termine(Nome)
		on update cascade
		on delete cascade
	,
	constraint fk_Tipologia foreign key(Tipologia) references Tipologia(Nome)
		on update cascade
		on delete cascade
	,
	constraint fk_TipoSist foreign key(Appartamento) references Sistemazione(Nome)
		on update cascade
		on delete cascade
	,
	constraint fk_prop foreign key (Proprietario) references Host(Email)
		on update cascade
		on delete cascade
);



create table Recensioni_Sistemazioni(
	Id integer,
	Sistemazione varchar(30),
	Descrizione varchar(200),
	Punteggio smallint,
	NumeroRisposte smallint,
	primary key(Id),
	foreign key(Sistemazione) references Sistemazione(Nome)
		on update cascade
		on delete cascade
);

create table Risposte(
	Id integer,
	Recensione integer,
	Descrizione varchar(200),
	Tipo boolean,
	primary key(Id),
	foreign key(Recensione) references Recensioni_Sistemazioni(Id)
		on update cascade
		on delete cascade
);

create table Recensioni_Utenti(
	Id integer,
	Utente varchar(30),
	Descrizione varchar(200),
	Punteggio smallint,
	primary key(Id),
	foreign key(Utente) references Utente(Email)
		on update cascade
		on delete cascade
);



create table Lingua(
	Nome varchar(20),
	primary key(Nome)
);

create table Parla(
	Utente varchar(30),
	Lingua varchar(20),
	primary key(Utente,Lingua),
	constraint  fk_Utente foreign key(Utente) references Utente(Email)
		on update cascade
		on delete cascade
	,
	constraint fk_Lingua foreign key(Lingua) references Lingua(Nome)
		on update cascade
		on delete cascade
);





create table Offerta(
	Servizio varchar(30),
	Sistemazione varchar(30),
	primary key(Servizio,Sistemazione),
	constraint fk_servizio foreign key(Servizio) references Servizio(Nome)
		on update cascade
		on delete cascade
	,
	constraint fk_sist foreign key(Sistemazione) references Sistemazione(Nome)
		on update cascade
		on delete cascade
);

create table Prenotazione(
	Id integer,
	Utente varchar(30),
	Sistemazione varchar(30),
	Check_in date,
	Check_out date,
	Fine_soggiorno boolean,
	primary key(Id),
	foreign key(Utente) references Utente(Email)
		on update cascade
		on delete cascade
	,
	foreign key(Sistemazione) references Sistemazione(Nome)
		on update cascade
		on delete cascade
);

create table Contiene(
	Sistemazione varchar(30),
	Tipo varchar(30),
	Numero_letti smallint,
	primary key(Sistemazione,Tipo),
	constraint fk_Sist foreign key(Sistemazione) references Sistemazione(Nome)
		on update cascade
		on delete cascade
	,
	constraint fk_TipoLetto foreign key(Tipo) references TipoLetto(Nome)
		on update cascade
		on delete cascade
);

