p(a).
p(b).
p(c).
p(d).
p(e).
p(f).
p(g).
p(h).


num(N) :- N = #count { X : p(X) }.

posto(1..N):-num(N).

postovicino(K,M) :- posto(K),posto(M),num(N),K+M=N+2, K!=M.

postovicino(K,M) :- K=1,posto(M),num(N),M=K+1;M=N.

postovicino(N,M) :- posto(M),num(N),M=N-1;M=1.

postovicino(K,M) :- posto(K), posto(M), M=K+1.

postovicino(K,M) :- posto(K), posto(M), M=K-1.

postovicino(1,N) :- num(N).

postovicino(N,1) :- num(N).

quasivicino(K,M) :-not postovicino(K,M),postovicino(M,P),postovicino(K,P),K!=M.

vuole(a,b).
nv(b,c).

%assegnazione dei posti alle persone.

{assign(X,P)} :- p(X), posto(P).

:- assign(X,P1), assign(X,P2), P1!=P2.

:- assign(X1,P), assign(X2,P), X1!=X2.

:- num(N),#count{X,P : assign(X,P)} != N.

%regola A: non mettere X vicino a Y se non vuole.

not assign(X,P) :-nv(X,Y),postovicino(P,Q), assign(Y,Q).

%regola B: quando è possibile, non mettere X e Y quasi vicini se non vogliono esserlo.

%not assign(X,P) :- nv(X,Y), quasivicino(P,Q),assign(Y,Q).

exc(X,Y,ruleB) :- nv(X,Y), quasivicino(P,Q), assign(X,P),assign(Y,Q).


%regola C: quando è possibile mettere X e Y vicini se lo vogliono.

exc(X,Y,ruleC) :- vuole(X,Y),not nv(Y,X),not postovicino(P,Q),assign(X,P),assign(Y,Q).

vuole(e,c).
nv(c,e).

#maximize{1@2,X,Y,ruleB : p(X),p(Y),not exc(X,Y,ruleB)}.
#maximize{1@1,X,Y,ruleC : p(X),p(Y),not exc(X,Y,ruleC)}.

#show assign/2.
%#show postovicino/2.
#show exc/3.