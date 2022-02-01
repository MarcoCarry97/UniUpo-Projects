:- lib(clpr).

ageconstraint(A,AS):-{A>=(AS+14)}.

base(BD,FD,A,AS):-ageconstraint(A,AS),{FD=BD}.


one(5,A,AS):-{A<18}.
one(5,A,AS):-{A>=60}.
one(5,A,AS):-{AS>=30}.
one(0,A,AS):-{A>=18,A<60}.
one(0,A,AS):-{AS<30}.

two(3,A,AS):-{AS>=30},{A>=60}.
two(0,A,AS):-{AS<30}.
two(0,A,AS):-{A<60}.

three(2,A,AS):-{AS>=15,AS<30}.
three(2,A,AS):-{A>=45}.
three(0,A,AS):-{AS<15}.
three(0,A,AS):-{AS>=30}.
three(0,A,AS):-{A<45}.

mutexrules([one,three]).

addrules([two]).

apply(R,FD,A,AS):-T=..[R,FD,A,AS],call(T).

mutex(FD,A,AS,L) :- mutexrules(RL), applymutex(RL,FD,A,AS,L).

applymutex([],0,_,_,[]).
applymutex([R|L],FD,A,AS,[R]):- apply(R,FD,A,AS).
applymutex([_|L],FD,A,AS,NL):- applymutex(L,FD,A,AS,NL).

add(FD,A,AS,L) :- addrules(RL), applyadd(RL,FD,A,AS,L).

applyadd([],0,_,_,[]).
applyadd([_|L],FD,A,AS,NL):- applyadd(L,FD,A,AS,NL).
applyadd([R|L],FD,A,AS,[R|NL]):- apply(R,FD1,A,AS), applyadd(L,FD2,A,AS,NL), {FD=FD1+FD2}.

rules(FD,A,AS,L):-mutex(FD1,A,AS,L1), add(FD2,A,AS,L2),append(L1,L2,L),{FD=FD1+FD2}.

days(BD,FD,A,AS,L) :- maximize(rules(FD2,A,AS,L),FD2),{FD=BD+FD2}.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

maximize(G, E) :- 
                      get_max_value(G, E, M),
                      {E = M},
                      call(G).
  
get_max_value(G, E, _) :-
        apply_new_bound(E),
        once(G),
	maximize(E), %% additional call to ensure ground result
        record_better_bound(E),
        fail.
get_max_value(_, _, M) :- erase(bestbound,M).
  
apply_new_bound(_).
apply_new_bound(E) :- 
                          erase(currentbound,B),
                          record(bestbound,B),
                          {E > B},
                          apply_new_bound(E).
  
record_better_bound(E) :- 
                         (erase(bestbound,_) -> true ; true),
                         record(currentbound,E).