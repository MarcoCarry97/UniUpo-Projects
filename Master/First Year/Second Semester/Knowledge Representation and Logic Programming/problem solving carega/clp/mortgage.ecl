:- lib(clpr).
%
% Standard mortgage relationship between:
%     P: Principal 	(ammontare del prestito)
%     T: Life of loan in months   
%     I: Fixed (but compounded) monthly interest rate 
%     B: Outstanding balance at the end    (eventuale saldo finale)
%     M: Monthly payment		   (rata mensile)

/* se dura 1 mese, pagare alla fine P + P*I - MP */

mg(P, T, I, B, MP) :-
  {
    T = 1,
    B = P + P*I - MP
  }.

/* se dura piu' di un mese, e' come un prestito di T1=T-1 mesi,
   con interesse I, saldo B, rata MP e importo P(I+1) - MP,
   infatti P*(I+1) e' la cifra dovuta con gli interessi,
   a cui si sottrae una rata */

mg(P, T, I, B, MP) :-
  {T > 1, P1 = P*(I+1) - MP, T1 = T-1},
  mg(P1,T1,I,B,MP).

?- printf("\n>>> Sample goal: mg(1000,T,0.1,0,X),{X < 200} \n", []).

incomev(LA,LT,MI,MD,R) :-{TI = LT * MI},{TD=LT*MD},{AD=TD+LA}, result(TI,AD,R).
result(TI,AD,ok):-{TI>AD}.
result(TI,AD,no):-{TI<AD}.

incomeval(P,LT,I,MI,MD,IT,R):-mg(P,LT,I,0,IT),{TR=IT*LT},incomev(TR,LT,MI,MD,R).


