% Modellare i possibili piani di studio della LM secondo il regolamento 
% della coorte 2020/21 
% usando i fatti qui indicati per i corsi considerati ai vari punti 
% del documento
% (al punto 5 qui si elencano solo i corsi attivati per il corso di studi)
%
% utilizzare un predicato scelto(corso,N) per rappresentare il fatto 
% che il "corso" viene scelto al punto N; 
% un corso non scelto ai punti 2 3 4 pu� essere scelto al punto 5

% il programma pu� essere usato per generare tutti i piani di studio, 
% o, ad esempio, indicando alcuni dei corsi scelti e trovando 
% le possibili soluzioni per gli altri

corso(1,calccomp,6).
corso(1,fondling,6).
corso(1,infret,6).

corso(2,compstat,6).
corso(2,datamin,6).
corso(2,metodiott,6).
corso(2,biocomp,3).
corso(2,dl,3).
corso(2,sisd,3).

corso(3,businta,9).
corso(3,mldl,9).
corso(3,intartsid,9).
corso(3,rclc,9).

corso(4,busintb,6).
corso(4,fwspsd,6).
corso(4,cybersec1,6).
corso(4,sismultimed,6).
corso(4,intart,6).
corso(4,hpc,6).
corso(4,mlearning,6).
corso(4,valprest,6).
corso(4,cybersec2,6).
corso(4,infforense,6).

corso(5,geomarketing,6).
corso(5,logcomp,3).
corso(5,appmobili,6).
corso(5,appweb,6).

totcorsiuno(N):- N=#count{C : corso(1,C,_)}.

%primo punto
{scelto(C,1)}  :- corso(1,C,_).
:- totcorsiuno(N),#count{C : scelto(C,1)}!=N.

%secondo punto
{scelto(C,2)} :- corso(2,C,U).
:-#sum{U,C : corso(2,C,U),scelto(C,2)}!=12.

%terzo punto
{scelto(C,3)} :- corso(3,C,U).
:- N=#count{C : corso(3,C,_),scelto(C,3)},N=2,N<4.


%quarto punto
{scelto(C,4)}:- corso(4,C,U).
%:-N=#sum{U,C : corso(3,C,U),scelto(C,3)},M=#sum{U,C : corso(4,C,U),scelto(C,4)},N+M!=39.
:-N=#sum{U,C : corso(3,C,U;4,C,U),scelto(C,3;C,4)},N!=39.


%quinto punto
{scelto(C,5)} :- corso(N,C,U), N>=2,N<=5.
:-#sum{U,C : corso(N,C,U),scelto(C,5)}!=12.

%limite 11 corsi per evitare frammentazione

:-M=#count{C : scelto(C,N), N>=1, N<5},M>12.

% no corsi già scelti

:-scelto(C,N),scelto(C,M),M!=N. 

%vincoli tra corsi

:-scelto(mldl,N1), scelto(dl,N2).
:-scelto(mldl,N1), scelto(mlearning,N2).
:-scelto(intartsid,N1), scelto(intart,N2).
:-scelto(intartsid,N1), scelto(sisd,N2).
:-scelto(rclc,N1), scelto(logcomp,N2).
:-scelto(rclc,N1), scelto(fwspsd,N2).
:-scelto(businta,N1), scelto(busintb,N2).

#show scelto/2.